#include "SmoothRenderer.h"

#include "../Graphics/Material.h"
#include "../Graphics/PointLight.h"

#include "../Shader/GLObjectFactory.h"
#include "TextureObject.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	constexpr char* projectionMatrixLabel = "projectionMatrix";
	constexpr char* modelviewMatrixLabel = "modelviewMatrix";
	constexpr char* eyePositionLabel = "eyePosition";
	constexpr char* positionLabel = "position";
	constexpr char* normalLabel = "normal";
	constexpr char* materialIdLabel = "materialId";
	constexpr char* texCoordLabel = "texCoord";
}

SmoothRenderer::SmoothRenderer()
{
}

ShaderBuildStatus SmoothRenderer::build(GLObjectFactory& factory)
{
	const auto& vsSource = getBuildInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	this->shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	if (!isOk) {
		ShaderBuildStatus status;
		status.isOk = false;
		status.log = shader->getLog();
		return status;
	}

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelviewMatrixLabel);
	shader->findUniformLocation(::eyePositionLabel);
	shader->findUniformLocation("ambientTexture");
	shader->findUniformLocation("diffuseTexture");
	shader->findUniformLocation("specularTexture");

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::normalLabel);
	//shader->findAttribLocation(::materialIdLabel);
	shader->findAttribLocation(::texCoordLabel);


	for (int i = 0; i < 1; ++i) {
		const auto prefix = "lights[" + std::to_string(i) + "]";
		shader->findUniformLocation(prefix + ".position");
		shader->findUniformLocation(prefix + ".La");
		shader->findUniformLocation(prefix + ".Ld");
		shader->findUniformLocation(prefix + ".Ls");
	}

	shader->findUniformLocation("material.Ka");
	shader->findUniformLocation("material.Ks");
	shader->findUniformLocation("material.Kd");
	shader->findUniformLocation("material.shininess");

	ShaderBuildStatus status;
	status.isOk = true;

	return status;
}

void SmoothRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void SmoothRenderer::sendLight(const int index, const PointLight& light)
{
	shader->bind();
	
	const auto prefix = "lights[" + std::to_string(index) + "]";

	const auto& lightPos = light.getPosition();//{ -10.0f, 10.0f, 10.0f };
	const auto& ambient = light.getAmbient();
	const auto& diffuse = light.getDiffuse();
	const auto& specular = light.getSpecular();

	shader->sendUniform(prefix + ".position", lightPos);
	shader->sendUniform(prefix + ".La", ambient);
	shader->sendUniform(prefix + ".Ld", diffuse);
	shader->sendUniform(prefix + ".Ls", specular);

	shader->unbind();
}

void SmoothRenderer::render(const Buffer& buffer)
{
	const auto& projectionMatrix = buffer.projectionMatrix;
	const auto& modelviewMatrix = buffer.modelViewMatrix;
	const auto& eyePos = buffer.eyePosition;

	shader->bind();

	shader->sendUniform(::projectionMatrixLabel, projectionMatrix);
	shader->sendUniform(::modelviewMatrixLabel, modelviewMatrix);
	shader->sendUniform(::eyePositionLabel, eyePos);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute3df(::normalLabel, buffer.normal);
	shader->sendVertexAttribute2df(::texCoordLabel, buffer.texCoord);
	//shader->sendVertexAttribute1di(::materialIdLabel, buffer.materialId);

	shader->bindOutput("fragColor");

	shader->enableDepthTest();


	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::normalLabel);
	shader->enableVertexAttribute(::texCoordLabel);
	//shader->enableVertexAttribute(::materialIdLabel);

	for (const auto& block : buffer.blocks) {
		shader->sendUniform("material.Ka", block.material.ambient);
		shader->sendUniform("material.Kd", block.material.diffuse);
		shader->sendUniform("material.Ks", block.material.specular);
		shader->sendUniform("material.shininess", block.material.shininess);

		block.texture->bind(0);
		shader->drawTriangles(block.vertexIndices.get());
		block.texture->unbind();
	}


	//shader->disableVertexAttribute(::materialIdLabel);
	shader->disableVertexAttribute(::texCoordLabel);
	shader->disableVertexAttribute(::normalLabel);
	shader->disableVertexAttribute(::positionLabel);

	assert(GL_NO_ERROR == glGetError());

	shader->disableDepthTest();
	shader->unbind();
}

std::string SmoothRenderer::getBuildInVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 normal;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec3 vNormal;" << std::endl
		<< "out vec3 vPosition;" << std::endl
		<< "out vec2 vTexCoord;" << std::endl
		<< "uniform mat4 projectionMatrix;"
		<< "uniform mat4 modelviewMatrix;"
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vNormal = normalize(normal);" << std::endl
		<< "	vPosition = position;" << std::endl
		<< "	vTexCoord = texCoord;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string SmoothRenderer::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 vNormal;" << std::endl
		<< "in vec3 vPosition;" << std::endl
		<< "in vec2 vTexCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "uniform vec3 eyePosition;" << std::endl
		<< "uniform sampler2D ambientTexture;" << std::endl
		<< "uniform sampler2D diffuseTexture;" << std::endl
		<< "uniform sampler2D specularTexture;" << std::endl
		<< "struct LightInfo {" << std::endl
		<< "	vec3 position;" << std::endl
		<< "	vec3 La;" << std::endl
		<< "	vec3 Ld;" << std::endl
		<< "	vec3 Ls;" << std::endl
		<< "};"
		<< "uniform LightInfo lights[8];" << std::endl
		<< "struct MaterialInfo {" << std::endl
		<< "	vec3 Ka;" << std::endl
		<< "	vec3 Kd;" << std::endl
		<< "	vec3 Ks;" << std::endl
		<< "	float shininess;" << std::endl
		<< "};"
		<< "uniform MaterialInfo material;" << std::endl
		<< "vec3 getAmbientColor(LightInfo light, MaterialInfo material){" << std::endl
		<< "	vec3 ambient = light.La * material.Ka;" << std::endl
		<< "	return ambient * texture2D(ambientTexture, vTexCoord).rgb;" << std::endl
		<< "};" << std::endl
		<< "vec3 getS(LightInfo light){" << std::endl
		<< "	return normalize(light.position - vPosition);" << std::endl
		<< "};" << std::endl
		<< "vec3 getV() {" << std::endl
		<< "	return normalize(vPosition - eyePosition);" << std::endl
		<< "};" << std::endl
		<< "vec3 getR(LightInfo light, vec3 normal) {" << std::endl
		<< "	vec3 s = getS(light);" << std::endl
		<< "	return reflect( -s, normal );" << std::endl
		<< "};" << std::endl
		<< "vec3 getDiffuseColor(LightInfo light, float innerProduct){" << std::endl
		<< "	vec3 diffuse = light.Ld * material.Kd * innerProduct;" << std::endl
		<< "	return diffuse * texture2D(diffuseTexture, vTexCoord).rgb;" << std::endl
		<< "};" << std::endl
		<< "vec3 getSpecularColor(LightInfo light, float innerProduct, vec3 normal){" << std::endl
		<< "	vec3 s = getS(light);" << std::endl
		<< "	vec3 v = getV();" << std::endl
		<< "	vec3 r = reflect( -s, normal );" << std::endl
		<< "	vec3 specular = vec3(0.0);" << std::endl
		<< "	if(innerProduct > 0.0) {" << std::endl
		<< "		specular = light.Ls * material.Ks * pow( max( dot(r,v), 0.0 ), material.shininess );" << std::endl
		<< "	}" << std::endl
		<< "	return specular * texture2D(specularTexture, vTexCoord).rgb;" << std::endl
		<< "};" << std::endl
		<< "vec3 getPhongShadedColor( vec3 position, vec3 normal) {"
		<< "	LightInfo light = lights[0];" << std::endl
		<< "	vec3 s = getS(light);" << std::endl
		<< "	vec3 r = getR(light, normal);" << std::endl
		<< "	vec3 ambient = getAmbientColor(light, material);" << std::endl
		<< "	float innerProduct = max( dot(s,normal), 0.0);" << std::endl
		<< "	vec3 diffuse = getDiffuseColor(light, innerProduct);" << std::endl
		<< "	vec3 specular = getSpecularColor(light, innerProduct, normal);" << std::endl
		<< "	return ambient + diffuse + specular;" << std::endl
		<< "}"
		<< "void main(void) {" << std::endl
		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal);" << std::endl
		//		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal) * getTextureColor();" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}