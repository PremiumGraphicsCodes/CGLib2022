#include "SkyBoxRenderer.h"

//#include "CameraShaderScene.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
//using namespace Crystal::Scene;


namespace {
	constexpr char* positionLabel = "position";
	constexpr char* projectionMatrixLabel = "projectionMatrix";
	constexpr char* modelViewMatrixLabel = "modelviewMatrix";
	constexpr char* fragColorLabel = "fragColor";
}

SkyBoxRenderer::SkyBoxRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus SkyBoxRenderer::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;
	status.isOk = true;

	const auto& vsSource = getBuiltInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	status.log = shader->getLog();
	if (!isOk) {
		status.isOk = false;
		return status;
	}

	/*
	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelViewMatrixLabel);

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::colorLabel);
	shader->findAttribLocation(::sizeLabel);
	*/

	return status;
}

void SkyBoxRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void SkyBoxRenderer::render(const Buffer& buffer)
{
	shader->bind();

	/*
	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute4df(::colorLabel, buffer.color);
	shader->sendVertexAttribute1df(::sizeLabel, buffer.size);

	shader->enableDepthTest();
	shader->enablePointSprite();

	shader->drawPoints(buffer.count);

	shader->bindOutput(::fragColorLabel);

	shader->disablePointSprite();
	shader->disableDepthTest();
	*/

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}

std::string SkyBoxRenderer::getBuiltInVertexShaderSource() const
{
	const std::string vsSource = R"(
#version 150
in vec3 position;
out vec3 vTexCoord;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void) {
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vTexCoord = position;
}
)";
	return vsSource;
}

std::string SkyBoxRenderer::getBuiltInFragmentShaderSource() const
{
	const std::string fsSource = R"(
#version 150
in vec3 vTexCoord;
out vec4 fragColor;
uniform samplerCube cubeMapTex;
void main(void) {
	fragColor = texture(cubeMapTex, vTexCoord);
}
)";
	return fsSource;
}