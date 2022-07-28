#include "DFLightRenderer.h"

#include "Crystal/Shader/TextureObject.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr auto positionLabel = "position";
	constexpr auto inverseModelViewMatrixLabel = "inverseModelViewMatrix";
	constexpr auto inverseProjectionMatrixLabel = "inverseProjectionMatrix";
}

DFLightRenderer::DFLightRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus DFLightRenderer::build(GLObjectFactory& factory)
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

	/*
	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelViewMatrixLabel);
	shader->findUniformLocation(::normalMatrixLabel);

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::normalLabel);
	*/

	ShaderBuildStatus status;
	status.isOk = true;
	return status;
}

void DFLightRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void DFLightRenderer::render(const Buffer& buffer)
{
	/*
	shader->bind();
	shader->bindOutput("gPosition", 0);
	shader->bindOutput("gNormal", 1);

	shader->enableDepthTest();


	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);
	shader->sendUniform(::normalMatrixLabel, buffer.normalMatrix);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute3df(::normalLabel, buffer.normal);

	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::normalLabel);

	shader->drawTriangles(buffer.indices);

	shader->disableVertexAttribute(::positionLabel);
	shader->disableVertexAttribute(::normalLabel);

	shader->disableDepthTest();


	shader->unbind();
	*/
}

std::string DFLightRenderer::getBuildInVertexShaderSource() const
{
	const std::string str = R"(
#version 150
in vec2 position;
out vec2 texCoord;
void main(void) {
	texCoord = (position + vec2(1.0,1.0))/2.0;
	gl_Position = vec4(position, 0.0, 1.0);
}
)";
	return str;
}

std::string DFLightRenderer::getBuiltInFragmentShaderSource() const
{
	const std::string str = R"(
#version 150
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D colorTexture;
uniform mat4 InvProjectionMatrix;
uniform mat4 InvModelViewMatrix;
uniform mat3 InvNormalMatrix;
struct Light {
	vec3 position;
	vec3 color;
};
uniform Light light;
in vec2 texCoord;
out vec4 fragColor;

vec3 getWorldPosition(vec3 pos)
{
	vec4 pos4 = InvModelViewMatrix * InvProjectionMatrix * vec4(pos, 1.0);
	return pos4.rgb;
}

vec3 getWorldNormal(vec3 normal)
{
	return InvNormalMatrix * normal;
}

vec3 getDiffuseColor(vec3 position, vec3 normal, vec3 color)
{
	vec3 lightDir = normalize(light.position - position);
	vec3 diffuse = max( dot(normal, lightDir), 0.0 ) * color * light.color;
	return diffuse;
}

void main(void) {
	vec3 pos = texture(positionTexture, texCoord).rgb;
	vec3 normal = texture(normalTexture, texCoord).rgb;
	vec3 worldPos = getWorldPosition(pos);
	vec3 worldNormal = getWorldNormal(normal);
	vec3 color = texture(colorTexture, texCoord).rgb;
	vec3 lighting = getDiffuseColor(worldPos, worldNormal, color); 
	fragColor = vec4(lighting, 1.0);
}
)";
	return str;
}
