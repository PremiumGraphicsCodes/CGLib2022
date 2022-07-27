#include "DFGeometryRenderer.h"

#include "Crystal/Shader/TextureObject.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto positionLabel = "position";
}

DFGeometryRenderer::DFGeometryRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus DFGeometryRenderer::build(GLObjectFactory& factory)
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

	ShaderBuildStatus status;
	status.isOk = true;
	return status;
}

void DFGeometryRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void DFGeometryRenderer::render(const Buffer& buffer)
{
	shader->bind();
	shader->bindOutput("gPosition");

	shader->enableDepthTest();


	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);

	shader->enableVertexAttribute(::positionLabel);

	shader->drawTriangles(buffer.indices);

	shader->disableVertexAttribute(::positionLabel);

	shader->disableDepthTest();


	shader->unbind();
}

std::string DFGeometryRenderer::getBuildInVertexShaderSource() const
{
	const std::string str = R"(
#version 150
in vec3 position;
out vec4 vPosition;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vPosition = gl_Position;
}
)";
	return str;
}

std::string DFGeometryRenderer::getBuiltInFragmentShaderSource() const
{
	const std::string str = R"(
#version 150
in vec4 vPosition;
out vec4 gPosition;

void main(void) {
	gPosition = vPosition;
}
)";
	return str;
}
