#include "DFPBLightRenderer.h"

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

DFPBLightRenderer::DFPBLightRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus DFPBLightRenderer::build(GLObjectFactory& factory)
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

	/*
	shader->findUniformLocation(::invProjectionMatrixLabel);
	shader->findUniformLocation(::invModelViewMatrixLabel);
	shader->findUniformLocation(::invNormalMatrixLabel);
	shader->findUniformLocation(::positionTextureLabel);
	shader->findUniformLocation(::normalTextureLabel);
	shader->findUniformLocation(::colorTextureLabel);
	shader->findUniformLocation("light.position");
	shader->findUniformLocation("light.color");

	shader->findAttribLocation(::positionLabel);
	*/

	return status;
}

void DFPBLightRenderer::release(GLObjectFactory& factory)
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

void DFPBLightRenderer::render(const Buffer& buffer)
{
	/*
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
	*/
}

std::string DFPBLightRenderer::getBuildInVertexShaderSource() const
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

std::string DFPBLightRenderer::getBuiltInFragmentShaderSource() const
{
	const std::string str = R"(
)";
	return str;
}
