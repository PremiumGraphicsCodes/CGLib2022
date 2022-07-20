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
	constexpr auto cubeMapTexLabel = "cubeMapTex";
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

	shader->drawTriangles(positions.size() / 3);

	buffer.cubeMapTexture->unbind();

	shader->bindOutput(::fragColorLabel);

	shader->unbind();

	shader->disableDepthTest();

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
	//fragColor.rgb = vec3(1,1,1);
}
)";
	return fsSource;
}