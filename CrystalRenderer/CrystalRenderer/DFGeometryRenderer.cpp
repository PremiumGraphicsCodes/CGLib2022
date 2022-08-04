#include "DFGeometryRenderer.h"

#include "Crystal/Shader/TextureObject.h"

#include <sstream>

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

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

ShaderBuildStatus DFGeometryRenderer::build()
{
	shader = std::make_unique<ShaderObject>();
	const auto isOk = shader->buildFromFile("../GLSL/DFGeometry.vs", "../GLSL/DFGeometry.fs");
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

void DFGeometryRenderer::render()
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
