#include "DepthTextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

DepthTextureObject::DepthTextureObject() :
	ITextureObject()
{}

void DepthTextureObject::send(const Imagef& image)
{
	this->width = image.getWidth();
	this->height = image.getHeight();

	//glActiveTexture(GL_TEXTURE0 + id);
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, image.getWidth(), image.getHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, image.getValues().data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	auto error = glGetError();

	glBindTexture(GL_TEXTURE_2D, 0);
	assert(GL_NO_ERROR == glGetError());
}

void DepthTextureObject::bind(const int slotNumber) const
{
	glActiveTexture(GL_TEXTURE0 + slotNumber);
	glBindTexture(GL_TEXTURE_2D, handle);
}

void DepthTextureObject::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

void DepthTextureObject::clear()
{
	glDeleteTextures(1, &handle);
}
