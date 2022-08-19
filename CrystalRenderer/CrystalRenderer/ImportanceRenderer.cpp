#include "ImportanceRenderer.h"

#include "GLCube.h"

using namespace Crystal::Math;
using namespace Crystal::Renderer;

namespace {
	constexpr auto envMapTex = "environmentMap";
	constexpr auto roughness = "roughness";
	constexpr auto positionLabel = "aPos";
	constexpr auto projectionMatrix = "projection";
	constexpr auto viewMatrix = "view";

}


ImportanceRenderer::ImportanceRenderer()
{}

void ImportanceRenderer::link()
{
	shader->findAttribLocation(::positionLabel);
	shader->findUniformLocation(::roughness);
	shader->findUniformLocation(::envMapTex);
	shader->findUniformLocation(::projectionMatrix);
	shader->findUniformLocation(::viewMatrix);
}

void ImportanceRenderer::render()
{
	const GLCube cube(Vector3df(-1, -1, -1), Vector3df(1, 1, 1));
	std::vector<float> positions = cube.toGLArray();

	shader->bind();

	shader->bindOutput("FragColor");

	buffer.evnMapTex->bind(0);

	shader->sendUniform(::envMapTex, 0);
	shader->sendUniform(::roughness, buffer.roughness);
	shader->sendUniform(::projectionMatrix, buffer.projectionMatrix);
	shader->sendUniform(::viewMatrix, buffer.viewMatrix);

	shader->sendVertexAttribute3df(::positionLabel, positions);

	glEnableVertexAttribArray(0);
	shader->drawTriangles(positions.size() / 3);
	glDisableVertexAttribArray(0);


	buffer.evnMapTex->unbind();

	shader->unbind();

}