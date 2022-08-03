#include "PBLightRenderer.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr auto projectionMatrixLabel = "projection";
	constexpr auto modelMatrixLabel = "model";
    constexpr auto viewMatrixLabel = "view";

    constexpr auto positionLabel = "aPos";
    constexpr auto normalLabel = "aNormal";

    constexpr auto albedoLabel = "albedo";
    constexpr auto metaricLabel = "metallic";
    constexpr auto roughbessLabel = "roughness";
    constexpr auto aoLabel = "ao";

    // lights
    //uniform vec3 lightPositions[4];
    //uniform vec3 lightColors[4];

    constexpr auto camerPosLabel = "camPos";
}

PBLightRenderer::PBLightRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus PBLightRenderer::build(GLObjectFactory& factory)
{
	const auto& vsSource = getBuildInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	if (!isOk) {
		ShaderBuildStatus status;
		status.isOk = false;
		status.log = shader->getLog();
		return status;
	}

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelMatrixLabel);
    shader->findUniformLocation(::viewMatrixLabel);

    shader->findUniformLocation(::albedoLabel);
    shader->findUniformLocation(::metaricLabel);
    shader->findUniformLocation(::roughbessLabel);
    shader->findUniformLocation(::aoLabel);

    shader->findUniformLocation(::camerPosLabel);

    for (int i = 0; i < 1; ++i) {
        shader->findUniformLocation("lightPositions[" + std::to_string(i) + "]");
        shader->findUniformLocation("lightColors[" + std::to_string(i) + "]");
    }

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::normalLabel);

	ShaderBuildStatus status;
	status.isOk = true;
	return status;
}

void PBLightRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void PBLightRenderer::render(const Buffer& buffer)
{
	shader->bind();
	shader->bindOutput("FragColor");

	shader->enableDepthTest();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelMatrixLabel, buffer.modelMatrix);
    shader->sendUniform(::viewMatrixLabel, buffer.viewMatrix);
    shader->sendUniform(::camerPosLabel, buffer.eyePosition);

    shader->sendUniform(::albedoLabel, buffer.albedo);
    shader->sendUniform(::metaricLabel, buffer.metalic);
    shader->sendUniform(::roughbessLabel, buffer.roughness);
    shader->sendUniform(::aoLabel, buffer.ao);

    shader->sendUniform("lightPositions[0]", buffer.lightPosition);
    shader->sendUniform("lightColors[0]", buffer.lightColor);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute3df(::normalLabel, buffer.normal);

    buffer.position.bind();
    buffer.normal.bind();
	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::normalLabel);

	shader->drawTriangles(buffer.indices);

	shader->disableVertexAttribute(::positionLabel);
	shader->disableVertexAttribute(::normalLabel);

	shader->disableDepthTest();

	shader->unbind();
}

#include <fstream>

std::string PBLightRenderer::getBuildInVertexShaderSource() const
{
    std::ifstream stream("../../GLSL/PBLight.vs");
    std::istreambuf_iterator<char> it(stream);
    std::istreambuf_iterator<char> last;
    std::string str(it, last);
    return str;
}

std::string PBLightRenderer::getBuiltInFragmentShaderSource() const
{
    std::ifstream stream("../../GLSL/PBLight.fs");
    std::istreambuf_iterator<char> it(stream);
    std::istreambuf_iterator<char> last;
    std::string str(it, last);
    return str;
}
