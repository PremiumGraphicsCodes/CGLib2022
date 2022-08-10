#include "CubeMapRenderer.h"

#include "Crystal/Shader/TextureObject.h"
#include "Crystal/Math/Box3d.h"

#include "Crystal/Shape/TriangleMeshBuilder.h"

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

namespace {
	std::vector<float> getCubePositions()
	{
        Crystal::Shape::TriangleMeshBuilder builder;
        Box3dd box(Vector3dd(-1, -1, -1), Vector3dd(1, 1, 1));
        builder.add(box, 2, 2, 2);
        const auto tm = builder.build();
        const auto fs = tm->getFaces();
        std::vector<float> positions;
        for (auto t : fs) {
            const auto v0 = t.triangle.getV0();
            const auto v1 = t.triangle.getV1();
            const auto v2 = t.triangle.getV2();
            positions.push_back(v0.x);
            positions.push_back(v0.y);
            positions.push_back(v0.z);
            positions.push_back(v1.x);
            positions.push_back(v1.y);
            positions.push_back(v1.z);
            positions.push_back(v2.x);
            positions.push_back(v2.y);
            positions.push_back(v2.z);
        }
        return positions;
	}
}

void CubeMapRenderer::render()
{
	shader->bind();

	std::vector<float> positions = getCubePositions();

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