#include "PolygonRenderer.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto positionLabel = "position";
	constexpr auto colorLabel = "color";
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

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::colorLabel);

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

	shader->sendVertexAttribute3df("position", buffer.position);
	shader->sendVertexAttribute4df("color", buffer.color);

	shader->enableVertexAttribute("position");
	shader->enableVertexAttribute("color");

	shader->drawTriangles(buffer.indices);

	shader->disableVertexAttribute("color");
	shader->disableVertexAttribute("position");

	shader->disableDepthTest();

	shader->unbind();
}

std::string PolygonRenderer::getBuildInVertexShaderSource() const
{
	const std::string str = R"(
#version 150
in vec3 position;
in vec4 color;
out vec4 vColor;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vColor = color;
}
)";
	return str;
}

std::string PolygonRenderer::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor = vColor;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}
