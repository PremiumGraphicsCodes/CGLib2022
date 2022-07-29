#include "DFLightRenderer.h"

#include "Crystal/Math/Box2d.h"
#include "Crystal/Shader/TextureObject.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Shader;

namespace {
	constexpr auto positionLabel = "position";
	constexpr auto positionTextureLabel = "positionTexture";
	constexpr auto normalTextureLabel = "normalTexture";
	constexpr auto colorTextureLabel = "colorTexture";
	constexpr auto invModelViewMatrixLabel = "invModelViewMatrix";
	constexpr auto invProjectionMatrixLabel = "invProjectionMatrix";
	constexpr auto invNormalMatrixLabel = "invNormalMatrix";
}

DFLightRenderer::DFLightRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus DFLightRenderer::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;
	status.isOk = true;

	const auto& vsSource = getBuildInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	if (!isOk) {
		status.isOk = false;
		status.log = shader->getLog();
		return status;
	}

	shader->findUniformLocation(::invProjectionMatrixLabel);
	shader->findUniformLocation(::invModelViewMatrixLabel);
	shader->findUniformLocation(::invNormalMatrixLabel);
	shader->findUniformLocation(::positionTextureLabel);
	shader->findUniformLocation(::normalTextureLabel);
	shader->findUniformLocation(::colorTextureLabel);
	shader->findUniformLocation("light.position");
	shader->findUniformLocation("light.color");

	shader->findAttribLocation(::positionLabel);

	return status;
}

void DFLightRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

namespace {
	std::vector<float> toArray(const Box2d<float>& box)
	{
		return{
			box.getMinX(), box.getMaxY(),
			box.getMinX(), box.getMinY(),
			box.getMaxX(), box.getMinY(),
			box.getMaxX(), box.getMaxY()
		};
	}
}

void DFLightRenderer::render(const Buffer& buffer)
{
	const Box2d<float> box(Vector2df(-1.0, -1.0), Vector2df(1.0, 1.0));
	const auto& positions = ::toArray(box);

	shader->bind();
	shader->bindOutput("fragColor", 0);

	shader->sendUniform(::invProjectionMatrixLabel, buffer.invProjectionMatrix);
	shader->sendUniform(::invModelViewMatrixLabel, buffer.invModelViewMatrix);
	shader->sendUniform(::invNormalMatrixLabel, buffer.invNormalMatrix);
	shader->sendUniform("light.position", buffer.lightPosition);
	shader->sendUniform("light.color", buffer.lightColor);

	buffer.positionTex->bind(0);
	buffer.normalTex->bind(1);
	buffer.albedoTex->bind(2);

	shader->sendUniform(::positionTextureLabel, 0);
	shader->sendUniform(::normalTextureLabel, 1);
	shader->sendUniform(::colorTextureLabel, *buffer.albedoTex, 2);

	glEnableVertexAttribArray(0);
	shader->sendVertexAttribute2df(::positionLabel, positions);
	shader->drawQuads(positions.size() / 2);
	glDisableVertexAttribArray(0);

	buffer.positionTex->unbind();
	buffer.normalTex->unbind();
	buffer.albedoTex->unbind();

	shader->unbind();
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
uniform mat4 invProjectionMatrix;
uniform mat4 invModelViewMatrix;
uniform mat3 invNormalMatrix;
struct Light {
	vec3 position;
	vec3 color;
};
uniform Light light;
in vec2 texCoord;
out vec4 fragColor;

vec3 getWorldPosition(vec3 pos)
{
	vec4 pos4 = invModelViewMatrix * invProjectionMatrix * vec4(pos, 1.0);
	return pos4.rgb;
}

vec3 getWorldNormal(vec3 normal)
{
	return invNormalMatrix * normal;
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
