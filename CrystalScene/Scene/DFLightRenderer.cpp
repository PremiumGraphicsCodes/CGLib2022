#include "DFLightRenderer.h"

#include "Crystal/Shader/TextureObject.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr auto positionLabel = "position";
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
uniform sampler2D texture;
in vec2 texCoord;
out vec4 fragColor;
void main(void) {
	fragColor = texture2D(texture, texCoord);
}
)";
	return str;
}
