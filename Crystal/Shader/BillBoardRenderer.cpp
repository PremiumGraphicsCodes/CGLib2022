#include "BillBoardRenderer.h"

#include "../Math/Vector2d.h"
#include "../Math/Box2d.h"

#include "GLObjectFactory.h"
#include "ITextureObject.h"

using namespace Crystal::Math;
//using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool BillBoardRenderer::build(GLObjectFactory& factory)
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	this->shader = factory.createShaderObject();
	if(!this->shader->build(vsSource, fsSource)) {
		return false;
	}
	findLocation();
	return true;
}

std::string BillBoardRenderer::getBuildinVertexShaderSource()
{
	const std::string str = R"(
#version 150
in vec2 position;
out vec2 texCoord;
void main(void) {" << std::endl
	texCoord = (position + vec2(1.0,1.0))/2.0;
	gl_Position = vec4(position, 0.0, 1.0);
}
)";
	return str;
}

std::string BillBoardRenderer::getBuildinFragmentShaderSource()
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

void BillBoardRenderer::findLocation()
{
	shader->findUniformLocation("texture");
	shader->findAttribLocation("position");
}

void BillBoardRenderer::render(const ITextureObject& texture)
{
	const Box2d box(Vector2df(-1.0, -1.0), Vector2df(1.0, 1.0));
	const auto& positions = box.toArray();

	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader->getHandle());

	texture.bind(0);

	glUniform1i(shader->getUniformLocation("texture"), 0);

	glVertexAttribPointer(shader->getAttribLocation("position"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>(positions.size() / 2));
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader->getHandle(), 0, "fragColor");

	texture.unbind();
	//glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}