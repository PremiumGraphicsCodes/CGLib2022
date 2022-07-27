#include "PolygonRenderer.h"

#include "Crystal/Shader/TextureObject.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto positionLabel = "position";
	constexpr auto texCoordLabel = "texCoord";
	constexpr auto textureLabel = "texture";
}

PolygonRenderer::PolygonRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus PolygonRenderer::build(GLObjectFactory& factory)
{
	const auto& vsSource = getBuildInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	if (!isOk) {
		ShaderBuildStatus status;
		status.isOk = false;
		status.log = shader->getLog();
		return status;
	}

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelViewMatrixLabel);
	shader->findUniformLocation(::textureLabel);

	shader->findUniformLocation("material.ambient");
	shader->findUniformLocation("material.diffuse");
	shader->findUniformLocation("material.specular");
	shader->findUniformLocation("material.shininess");

	shader->findUniformLocation("light.position");
	shader->findUniformLocation("light.ambient");
	shader->findUniformLocation("light.diffuse");
	shader->findUniformLocation("light.specular");

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::texCoordLabel);

	ShaderBuildStatus status;
	status.isOk = true;
	return status;
}

void PolygonRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void PolygonRenderer::render(const Buffer& buffer)
{
	shader->bind();
	shader->bindOutput("fragColor");

	shader->enableDepthTest();


	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute2df(::texCoordLabel, buffer.texCoord);

	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::texCoordLabel);

	for(const auto& fg : buffer.faceGroups) {
		shader->sendUniform(::textureLabel, *fg.texture, 0);
		fg.texture->bind(0);
		shader->drawTriangles(fg.indices);
		fg.texture->unbind();
	}

	shader->disableVertexAttribute(::positionLabel);
	shader->disableVertexAttribute(::texCoordLabel);

	shader->disableDepthTest();


	shader->unbind();
}

std::string PolygonRenderer::getBuildInVertexShaderSource() const
{
	const std::string str = R"(
#version 150
in vec3 position;
in vec2 texCoord;
out vec2 vTexCoord;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vTexCoord = texCoord;
}
)";
	return str;
}

std::string PolygonRenderer::getBuiltInFragmentShaderSource() const
{
	const std::string str = R"(
#version 150
in vec2 vTexCoord;
out vec4 fragColor;
struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Light light;
uniform Material material;
uniform sampler2D texture;

/*
vec3 getPhongShadedColor(vec3 position, vec3 normal) {

}
*/

void main(void) {
	fragColor.rgb = light.position;
	fragColor.rgb = light.ambient;
	fragColor.rgb = light.diffuse;
	fragColor.rgb = light.specular;

	fragColor.rgb = material.ambient;
	fragColor.rgb = material.diffuse;
	fragColor.rgb = material.specular;
	fragColor.r = material.shininess;
	fragColor = texture2D(texture, vTexCoord);
}
)";
	return str;
}