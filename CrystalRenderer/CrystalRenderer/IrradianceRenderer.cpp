#include "IrradianceRenderer.h"

using namespace Crystal::Shader;

namespace {
    constexpr auto projectionMatrixLabel = "projection";
    constexpr auto viewMatrixLabel = "view";
    constexpr auto cubeMapTexLabel = "environmentMap";
    constexpr auto positionLabel = "aPos";
}

IrradianceRenderer::IrradianceRenderer() :
    shader(nullptr)
{}

ShaderBuildStatus IrradianceRenderer::build(GLObjectFactory& factory)
{
    shader = factory.createShaderObject();
    const auto isOk = shader->build("../GLSL/Irradiance.vs", "../GLSL/Irradiance.fs");
    if (!isOk) {
        ShaderBuildStatus status;
        status.isOk = false;
        status.log = shader->getLog();
        return status;
    }

    shader->findUniformLocation(::projectionMatrixLabel);
    shader->findUniformLocation(::viewMatrixLabel);
    shader->findUniformLocation(::cubeMapTexLabel);
    
    shader->findAttribLocation(::positionLabel);

    ShaderBuildStatus status;
    status.isOk = true;
    return status;
}

void IrradianceRenderer::release(Shader::GLObjectFactory& factory)
{

}

void IrradianceRenderer::render(const Buffer& buffer)
{

}