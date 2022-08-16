#include "IrradianceRenderer.h"

#include "GLCube.h"

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

void IrradianceRenderer::render()
{
    const GLCube cube(Vector3df(-1, -1, -1), Vector3df(1, 1, 1));
    const auto positions = cube.toGLArray();

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