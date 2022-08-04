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

void DFGeometryRenderer::setShader(std::unique_ptr<Shader::ShaderObject> shader)
{
	this->shader = std::move(shader);

	this->shader->findUniformLocation(::projectionMatrixLabel);
	this->shader->findUniformLocation(::modelViewMatrixLabel);
	this->shader->findUniformLocation(::normalMatrixLabel);

	this->shader->findAttribLocation(::positionLabel);
	this->shader->findAttribLocation(::normalLabel);
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
