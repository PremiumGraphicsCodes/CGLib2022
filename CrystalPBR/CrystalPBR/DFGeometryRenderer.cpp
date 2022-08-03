#include "DFGeometryRenderer.h"

#include "Crystal/Shader/TextureObject.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto normalMatrixLabel = "normalMatrix";
	constexpr auto positionLabel = "position";
	constexpr auto normalLabel = "normal";
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
	shader->findUniformLocation(::normalMatrixLabel);

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::normalLabel);

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
}

#include <fstream>

std::string DFGeometryRenderer::getBuildInVertexShaderSource() const
{
	std::ifstream stream("../../GLSL/DFGeometry.vs");
	std::istreambuf_iterator<char> it(stream);
	std::istreambuf_iterator<char> last;
	std::string str(it, last);
	return str;
}

std::string DFGeometryRenderer::getBuiltInFragmentShaderSource() const
{
	std::ifstream stream("../../GLSL/DFGeometry.fs");
	std::istreambuf_iterator<char> it(stream);
	std::istreambuf_iterator<char> last;
	std::string str(it, last);
	return str;
}
