#include "PointRenderer.h"

//#include "CameraShaderScene.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
//using namespace Crystal::Scene;


namespace {
	constexpr char* positionLabel = "position";
	constexpr char* colorLabel = "color";
	constexpr char* sizeLabel = "pointSize";
	constexpr char* projectionMatrixLabel = "projectionMatrix";
	constexpr char* modelViewMatrixLabel = "modelviewMatrix";
	constexpr char* fragColorLabel = "fragColor";
}

PointRenderer::PointRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus PointRenderer::build(GLObjectFactory& factory)
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

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::colorLabel);
	shader->findAttribLocation(::sizeLabel);

	return status;
}

void PointRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void PointRenderer::render(const Buffer& buffer)
{
	shader->bind();

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

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());
}

void PointRenderer::renderBlend(const Buffer& buffer)
{
	shader->bind();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelViewMatrixLabel, buffer.modelViewMatrix);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute4df(::colorLabel, buffer.color);
	shader->sendVertexAttribute1df(::sizeLabel, buffer.size);

	//shader.enableDepthTest();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader->enablePointSprite();

	shader->drawPoints(buffer.count);

	shader->bindOutput(::fragColorLabel);

	shader->disablePointSprite();

	glDisable(GL_BLEND);
	//shader.disableDepthTest();

	shader->unbind();

	assert(GL_NO_ERROR == glGetError());

}

std::string PointRenderer::getBuiltInVertexShaderSource() const
{
	const std::string vsSource = R"(
#version 150
in vec3 position;
in float pointSize;
in vec4 color;
out vec4 vColor;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
void main(void) {
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	gl_PointSize = pointSize / gl_Position.w;
	vColor = color;
}
)";
	return vsSource;
}

std::string PointRenderer::getBuiltInFragmentShaderSource() const
{
	const std::string fsSource = R"(
#version 150
in vec4 vColor;
out vec4 fragColor;
void main(void) {
	vec2 coord = gl_PointCoord * 2.0 - 1.0;
	float distSquared = 1.0 - dot(coord, coord);
	if (distSquared < 0.0) {
		discard;
	}
	fragColor.rgba = vColor;
	//fragColor.a = sqrt(distSquared) * vColor.a;
	//fragColor.a = 0.1;//sqrt(distSquared);
}
)";
	return fsSource;
}