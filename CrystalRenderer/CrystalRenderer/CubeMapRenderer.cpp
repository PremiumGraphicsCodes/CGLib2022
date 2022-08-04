#include "CubeMapRenderer.h"

#include "Crystal/Shader/TextureObject.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto projectionMatrixLabel = "projection";
	constexpr auto viewMatrixLabel = "view";
	constexpr auto textureLabel = "equirectangularMap";
	constexpr auto positionLabel = "aPos";
	constexpr auto fragColorLabel = "FragColor";
}

CubeMapRenderer::CubeMapRenderer() :
	shader(nullptr)
{
}

void CubeMapRenderer::setShader(std::unique_ptr<ShaderObject> shader)
{
	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::viewMatrixLabel);
	shader->findUniformLocation(::textureLabel);

	shader->findAttribLocation(::positionLabel);
}

namespace {
	std::vector<float> getCubePositions()
	{
		return {};
	}
}

void CubeMapRenderer::render()
{
	shader->bind();

	std::vector<float> positions = getCubePositions();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::viewMatrixLabel, buffer.modelViewMatrix);

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