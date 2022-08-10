#include "IrradianceRenderer.h"

using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
    constexpr auto projectionMatrixLabel = "projection";
    constexpr auto viewMatrixLabel = "view";
    constexpr auto cubeMapTexLabel = "environmentMap";
    constexpr auto positionLabel = "aPos";
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

}