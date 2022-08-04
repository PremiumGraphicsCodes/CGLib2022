#include "SkyBoxRenderer.h"

//#include "CameraShaderScene.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
//using namespace Crystal::Scene;


namespace {
	constexpr auto positionLabel = "position";
	constexpr auto projectionMatrixLabel = "projectionMatrix";
	constexpr auto modelViewMatrixLabel = "modelviewMatrix";
	constexpr auto cubeMapTexLabel = "cubeMapTex";
	constexpr auto fragColorLabel = "fragColor";
}

SkyBoxRenderer::SkyBoxRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus SkyBoxRenderer::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;
	status.isOk = true;

	shader = factory.createShaderObject();
	const auto isOk = shader->build("../../GLSL/SkyBox.vs", "../../GLSL/SkyBox.fs");
	status.log = shader->getLog();
	if (!isOk) {
		status.isOk = false;
		return status;
	}

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelViewMatrixLabel);
	shader->findUniformLocation(::cubeMapTexLabel);

	shader->findAttribLocation(::positionLabel);

	return status;
}

void SkyBoxRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void SkyBoxRenderer::render(const Buffer& buffer)
{
	shader->bind();

	std::vector<float> positions = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	shader->enableDepthTest();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	buffer.cubeMapTexture->bind(0);

	shader->sendUniform(cubeMapTexLabel, 0);

	shader->sendVertexAttribute3df(::positionLabel, positions);

	glEnableVertexAttribArray(0);
	shader->drawTriangles(positions.size() / 3);
	glDisableVertexAttribArray(0);

	buffer.cubeMapTexture->unbind();

	shader->bindOutput(::fragColorLabel);

	shader->unbind();

	shader->disableDepthTest();

	assert(GL_NO_ERROR == glGetError());
}