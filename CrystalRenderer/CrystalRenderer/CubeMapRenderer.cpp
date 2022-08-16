#include "CubeMapRenderer.h"

#include "Crystal/Shader/TextureObject.h"
#include "Crystal/Math/Box3d.h"

#include "GLCube.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projection";
	constexpr auto viewMatrixLabel = "view";
	constexpr auto textureLabel = "equirectangularMap";
	constexpr auto positionLabel = "aPos";
	constexpr auto fragColorLabel = "FragColor";
}

CubeMapRenderer::CubeMapRenderer()
{
}

void CubeMapRenderer::link()
{
	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::viewMatrixLabel);
	shader->findUniformLocation(::textureLabel);

	shader->findAttribLocation(::positionLabel);
}

void CubeMapRenderer::render()
{
	shader->bind();

	const GLCube cube(Vector3df(-1, -1, -1), Vector3df(1, 1, 1));
	std::vector<float> positions = cube.toGLArray();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::viewMatrixLabel, buffer.viewMatrix);

	buffer.texture->bind(0);

	shader->sendUniform(textureLabel, 0);

	shader->sendVertexAttribute3df(::positionLabel, positions);

	glEnableVertexAttribArray(0);
    shader->drawTriangles(positions.size() / 3);
	glDisableVertexAttribArray(0);

	buffer.texture->unbind();

	shader->bindOutput(::fragColorLabel);

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}