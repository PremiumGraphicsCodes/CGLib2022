#include "DepthBuffer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool DepthBuffer::build(DepthTextureObject* depthTexture)
{
	this->texture = depthTexture;
	this->width = depthTexture->getWidth();
	this->height = depthTexture->getHeight();
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->getHandle(), 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return (GL_NO_ERROR == glGetError());
}

void DepthBuffer::setTexture(DepthTextureObject* texture)
{
	this->texture = texture;
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->getHandle(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool DepthBuffer::bind(const int slotNumber) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	texture->bind(slotNumber);
	return (GL_NO_ERROR == glGetError());
}

bool DepthBuffer::unbind() const
{
	texture->unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return (GL_NO_ERROR == glGetError());
}