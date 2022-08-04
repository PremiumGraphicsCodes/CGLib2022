#include "CubeMapRenderer.h"

#include "Crystal/Shader/TextureObject.h"

using namespace Crystal::Shader;

namespace {
	constexpr auto projectionMatrixLabel = "projection";
	constexpr auto viewMatrixLabel = "view";
	constexpr auto textureLabel = "equirectangularMap";
	constexpr auto positionLabel = "aPos";
	constexpr auto fragColorLabel = "FragColor";
}

CubeMapRenderer::CubeMapRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus CubeMapRenderer::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;
	status.isOk = true;

	const auto& vsSource = getBuiltInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	status.log = shader->getLog();
	if (!isOk) {
		status.isOk = false;
		return status;
	}

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::viewMatrixLabel);
	shader->findUniformLocation(::textureLabel);

	shader->findAttribLocation(::positionLabel);

	return status;
}

void CubeMapRenderer::release(GLObjectFactory& factory)
{

}

namespace {
	std::vector<float> getCubePositions()
	{
		return {};
	}
}

void CubeMapRenderer::render(const Buffer& buffer)
{
	shader->bind();

	std::vector<float> positions = getCubePositions();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::viewMatrixLabel, buffer.modelViewMatrix);

	buffer.texture->bind(0);

	shader->sendUniform(textureLabel, 0);

	shader->sendVertexAttribute3df(::positionLabel, positions);

	glEnableVertexAttribArray(0);
	shader->drawTriangles(positions.size() / 3);
	glDisableVertexAttribArray(0);

	buffer.texture->unbind();

	shader->bindOutput(::fragColorLabel);

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}

std::string CubeMapRenderer::getBuiltInVertexShaderSource() const
{
	const std::string str = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 WorldPos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    WorldPos = aPos;  
    gl_Position =  projection * view * vec4(WorldPos, 1.0);
}
)";
	return str;
}

std::string CubeMapRenderer::getBuiltInFragmentShaderSource() const
{
	const std::string str = R"(
#version 330 core
out vec4 FragColor;
in vec3 WorldPos;

uniform sampler2D equirectangularMap;

const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main()
{		
    vec2 uv = SampleSphericalMap(normalize(WorldPos));
    vec3 color = texture(equirectangularMap, uv).rgb;
    
    FragColor = vec4(color, 1.0);
}

)";
	return str;
}
