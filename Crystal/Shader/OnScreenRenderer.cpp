#include "OnScreenRenderer.h"

#include "../Math/Vector2d.h"
#include "../Math/Box2d.h"

#include "GLObjectFactory.h"
#include "TextureObject.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

ShaderBuildStatus OnScreenRenderer::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	this->shader = factory.createShaderObject();
	if(!this->shader->build(vsSource, fsSource)){
		status.isOk = false;
		status.log += this->shader->getLog();
		return status;
	}
	findLocation();
	return status;
}

void OnScreenRenderer::release(GLObjectFactory& factory)
{
	factory.remove(this->shader);
}

std::string OnScreenRenderer::getBuildinVertexShaderSource()
{
	const std::string str = R"(
#version 150
in vec2 position;
out vec2 texCoord;
void main(void) {
	texCoord = (position + vec2(1.0,1.0))/2.0;
	gl_Position = vec4(position, 0.0, 1.0);
}
)";
	return str;
}

std::string OnScreenRenderer::getBuildinFragmentShaderSource()
{
	const std::string str = R"(
#version 150
uniform sampler2D texture;
in vec2 texCoord;
out vec4 fragColor;
void main(void) {
	fragColor = texture2D(texture, texCoord);
}
)";
	return str;
}

void OnScreenRenderer::findLocation()
{
	shader->findUniformLocation("texture");
	shader->findAttribLocation("position");
}

void OnScreenRenderer::render(const ITextureObject& texture)
{
	const Box2d box(Vector2df(-1.0, -1.0), Vector2df(1.0, 1.0));
	const auto& positions = box.toArray();

	//glEnable(GL_DEPTH_TEST);

	shader->bind();
	//glUseProgram(shader->getHandle());

	texture.bind(0);

	//glUniform1i(shader->getUniformLocation("texture"), 0);
	shader->sendUniform("texture", texture, 0);

	glVertexAttribPointer(shader->getAttribLocation("position"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));
	glDisableVertexAttribArray(0);

	shader->bindOutput("fragColor");

	texture.unbind();
	//glDisable(GL_DEPTH_TEST);

	shader->unbind();
}