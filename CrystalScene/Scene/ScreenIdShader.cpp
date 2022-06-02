#include "ScreenIdShader.h"

#include "Crystal/Shader/GLObjectFactory.h"

#include "PointShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ScreenIdShader::ScreenIdShader(const std::string& name)
{
}

bool ScreenIdShader::build(GLObjectFactory& factory)
{
	//frameBufferObject;
	frameBufferObject.build(512, 512);

	texture = factory.createTextureObject();
	texture->send(Image(512, 512));
	//texture = factory.getTextureFactory()->createTextureObject("SceneId", Imagef(512, 512));

	return true;
}

void ScreenIdShader::release(GLObjectFactory& factory)
{

}

void ScreenIdShader::render(const Graphics::Camera& camera)
{
	frameBufferObject.setTexture(*texture);
	//texture.bind();
	frameBufferObject.bind();
	glViewport(0, 0, texture->getWidth(), texture->getHeight());
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto s : scenes) {
		s->render(camera);
	}

	frameBufferObject.unbind();
}

DrawableID ScreenIdShader::getId(const double x, const double y)
{
	const auto ix = static_cast<int>(x * texture->getWidth());
	const auto iy = static_cast<int>(y * texture->getHeight());
	return getIdInTexCoord(ix, iy);
}

DrawableID ScreenIdShader::getIdInTexCoord(const int x, const int y)
{
	frameBufferObject.bind();
	glViewport(0, 0, texture->getWidth(), texture->getHeight());
	const auto& color = frameBufferObject.getColor(x, y);
	frameBufferObject.unbind();
	return DrawableID(color);
}