#include "LineRenderer.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr const char* positionLabel = "position";
	constexpr const char* colorLabel = "color";
	constexpr const char* projectionMatrixLabel = "projectionMatrix";
	constexpr const char* modelViewMatrixLabel = "modelviewMatrix";
	constexpr const char* fragColorLabel = "fragColor";
}

LineRenderer::LineRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus LineRenderer::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	const auto& vsSource = getBuiltInVsSource();
	const auto& fsSource = getBuiltInFsSource();

	this->shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	if (!isOk) {
		status.isOk = false;
		status.log = shader->getLog();
		return status;
	}

	status.isOk = true;

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelViewMatrixLabel);

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::colorLabel);

	return status;
}

void LineRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void LineRenderer::render(const Buffer& buffer)
{
	if (buffer.indices.empty()) {
		return;
	}
	shader->bind();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	shader->setLineWidth(buffer.lineWidth);
	shader->enableDepthTest();

	shader->sendVertexAttribute3df(positionLabel, *buffer.position);
	shader->sendVertexAttribute4df(colorLabel, *buffer.color);

	shader->drawLines(buffer.indices);

	//shader->disableVertexAttribute("color");
	//shader->disableVertexAttribute("position");

	shader->bindOutput(::fragColorLabel);

	shader->setLineWidth(1);
	shader->disableDepthTest();

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}

std::string LineRenderer::getBuiltInVsSource() const
{
	const std::string str = R"(
#version 150
in vec3 position;
in vec4 color;
out vec4 vColor;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;

void main(void) {
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vColor = color;
}
)";
	return str;
}

std::string LineRenderer::getBuiltInFsSource() const
{
	const std::string str = R"(
#version 150
in vec4 vColor;
out vec4 fragColor;

void main(void) {
	fragColor = vColor;
}
)";
	return str;
}