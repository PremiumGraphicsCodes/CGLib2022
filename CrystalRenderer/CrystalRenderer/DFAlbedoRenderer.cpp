#include "DFAlbedoRenderer.h"

#include "Crystal/Shader/TextureObject.h"

#include <sstream>

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto positionLabel = "position";
	constexpr auto texCoordLabel = "texCoord";
	constexpr auto textureLabel = "texture";
}

DFAlbedoRenderer::DFAlbedoRenderer()
{
}

void DFAlbedoRenderer::link()
{
	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelViewMatrixLabel);
	shader->findUniformLocation(::textureLabel);

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::texCoordLabel);
}

void DFAlbedoRenderer::render()
{
	shader->bind();
	shader->bindOutput("fragColor");

	shader->enableDepthTest();


	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute2df(::texCoordLabel, buffer.texCoord);

	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::texCoordLabel);

	for (const auto& fg : buffer.faceGroups) {
		shader->sendUniform(::textureLabel, *fg.texture, 0);
		fg.texture->bind(0);
		shader->drawTriangles(fg.indices);
		fg.texture->unbind();
	}

	shader->disableVertexAttribute(::positionLabel);
	shader->disableVertexAttribute(::texCoordLabel);

	shader->disableDepthTest();


	shader->unbind();
}