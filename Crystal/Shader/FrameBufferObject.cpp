#include "FrameBufferObject.h"

//#include "glew.h"
#include "TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void FrameBufferObject::build(int width, int height)
{
	this->width = width;
	this->height = height;
	glGenFramebuffers(1, &frameBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	assert(GL_NO_ERROR == glGetError());
}

void FrameBufferObject::clear()
{
	glDeleteRenderbuffers(1, &depthBuffer);
	glDeleteFramebuffers(1, &frameBuffer);
}

void FrameBufferObject::setTexture(const ITextureObject& texture)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getHandle(), 0);

	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBufferObject::setTexture(const ITextureObject& texture, unsigned int number)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + number, GL_TEXTURE_2D, texture.getHandle(), 0);
}


void FrameBufferObject::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//glBindTexture(GL_TEXTURE_2D, texture.getId());
	assert(GL_NO_ERROR == glGetError());
}

void FrameBufferObject::unbind()
{
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	assert(GL_NO_ERROR == glGetError());
}

Image FrameBufferObject::toImage() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(width * height * 4);

	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return Image(width, height, values);
}

ColorRGBAuc FrameBufferObject::getColor(const int x, const int y) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(4);

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return ColorRGBAuc(values[0], values[1], values[2], values[3]);
}

ColorRGBAf FrameBufferObject::getColorf(const int x, const int y) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<float> values(4);

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return ColorRGBAf(values[0], values[1], values[2], values[3]);
}

std::vector<ColorRGBAuc> FrameBufferObject::getColors(const int x, const int y, const int width, const int height) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(width * height * 4);

	glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::vector<ColorRGBAuc> results;
	for (int i = 0; i < values.size(); i += 4) {
		results.push_back(ColorRGBAuc(values[i + 0], values[i + 1], values[i + 2], values[i + 3]));
	}

	return results;
}

std::vector<ColorRGBAf> FrameBufferObject::getColorsf(const int x, const int y, const int width, const int height) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<float> values(width * height * 4);

	glReadPixels(x, y, width, height, GL_RGBA, GL_FLOAT, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::vector<ColorRGBAf> results;
	for (int i = 0; i < values.size(); i += 4) {
		results.push_back(ColorRGBAf(values[i + 0], values[i + 1], values[i + 2], values[i + 3]));
	}

	return results;
}