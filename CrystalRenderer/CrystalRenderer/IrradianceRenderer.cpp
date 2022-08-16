#include "IrradianceRenderer.h"

#include "Crystal/Shape/TriangleMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
    constexpr auto projectionMatrixLabel = "projection";
    constexpr auto viewMatrixLabel = "view";
    constexpr auto cubeMapTexLabel = "environmentMap";
    constexpr auto positionLabel = "aPos";
    constexpr auto fragColorLabel = "FragColor";
}

IrradianceRenderer::IrradianceRenderer()
{}

void IrradianceRenderer::link()
{
    shader->findUniformLocation(::projectionMatrixLabel);
    shader->findUniformLocation(::viewMatrixLabel);
    shader->findUniformLocation(::cubeMapTexLabel);
    
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

void IrradianceRenderer::render()
{
    const auto positions = ::getCubePositions();

    shader->bind();

    buffer.cubeMapTex->bind(0);
    shader->sendUniform(::cubeMapTexLabel, 0);
    shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
    shader->sendUniform(::viewMatrixLabel, buffer.viewMatrix);

    shader->bindOutput(::fragColorLabel);

    shader->sendVertexAttribute3df(::positionLabel, positions);

    glEnableVertexAttribArray(0);
    shader->drawTriangles(positions.size() / 3);
    glDisableVertexAttribArray(0);


    buffer.cubeMapTex->unbind();

    shader->unbind();
}