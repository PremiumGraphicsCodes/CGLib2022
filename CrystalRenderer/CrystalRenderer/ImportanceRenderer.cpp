#include "ImportanceRenderer.h"

using namespace Crystal::Renderer;

namespace {
	constexpr auto envMapTex = "environmentMap";
	constexpr auto roughness = "roughness";
	constexpr auto position = "aPos";
	constexpr auto projectionMatrix = "projection";
	constexpr auto viewMatrix = "view";

}


ImportanceRenderer::ImportanceRenderer()
{}

void ImportanceRenderer::link()
{
	shader->findAttribLocation(::position);
	shader->findUniformLocation(::roughness);
	shader->findUniformLocation(::envMapTex);
	shader->findUniformLocation(::projectionMatrix);
	shader->findUniformLocation(::viewMatrix);
}

void ImportanceRenderer::render()
{
	shader->bind();

	shader->bindOutput("FragColor");

	buffer.evnMapTex->bind(0);

	shader->sendUniform(::envMapTex, 0);
	shader->sendUniform(::roughness, buffer.roughness);
	shader->sendUniform(::projectionMatrix, buffer.projectionMatrix);
	shader->sendUniform(::viewMatrix, buffer.viewMatrix);

	shader->sendVertexAttribute3df(::position, *buffer.positions);

	glEnableVertexAttribArray(0);
	shader->drawTriangles(buffer.indices);
	glDisableVertexAttribArray(0);

	buffer.evnMapTex->unbind();

	shader->unbind();

}