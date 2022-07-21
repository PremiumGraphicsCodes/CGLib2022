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
	const std::string str = R"(
#version 150
in vec3 position;
in vec3 normal;
in vec2 texCoord;
out vec3 vNormal;
out vec3 vPosition;
out vec2 vTexCoord;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void) {
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vNormal = normalize(normal);
	vPosition = position;
	vTexCoord = texCoord;
};
)";
	return str;
}

std::string SmoothRenderer::getBuiltInFragmentShaderSource() const
{
	const std::string str = R"(
#version 150
in vec3 vNormal;
in vec3 vPosition;
in vec2 vTexCoord;
out vec4 fragColor;
uniform vec3 eyePosition;
uniform sampler2D ambientTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
struct LightInfo {
	vec3 position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};
uniform LightInfo lights[8];
struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float shininess;
};
uniform MaterialInfo material;
vec3 getAmbientColor(LightInfo light, MaterialInfo material){
	vec3 ambient = light.La * material.Ka;
	return ambient * texture2D(ambientTexture, vTexCoord).rgb;
};
vec3 getS(LightInfo light){
	return normalize(light.position - vPosition);
};
vec3 getV() {
	return normalize(vPosition - eyePosition);
};
vec3 getR(LightInfo light, vec3 normal) {
	vec3 s = getS(light);
	return reflect( -s, normal );
};
vec3 getDiffuseColor(LightInfo light, float innerProduct){
	vec3 diffuse = light.Ld * material.Kd * innerProduct;
	return diffuse * texture2D(diffuseTexture, vTexCoord).rgb;
};
vec3 getSpecularColor(LightInfo light, float innerProduct, vec3 normal){
	vec3 s = getS(light);
	vec3 v = getV();
	vec3 r = reflect( -s, normal );
	vec3 specular = vec3(0.0);
	if(innerProduct > 0.0) {
		specular = light.Ls * material.Ks * pow( max( dot(r,v), 0.0 ), material.shininess );
	}
	return specular * texture2D(specularTexture, vTexCoord).rgb;
};
vec3 getPhongShadedColor( vec3 position, vec3 normal) {
	LightInfo light = lights[0];
	vec3 s = getS(light);
	vec3 r = getR(light, normal);
	vec3 ambient = getAmbientColor(light, material);
	float innerProduct = max( dot(s,normal), 0.0);
	vec3 diffuse = getDiffuseColor(light, innerProduct);
	vec3 specular = getSpecularColor(light, innerProduct, normal);
	return ambient + diffuse + specular;
}
void main(void) {
	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal);
		//	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal) * getTextureColor();
	fragColor.a = 1.0;
};
)";
	return str;
}