#include "RenderBufferObject.h"

using namespace Crystal::Shader;

RenderBufferObject::~RenderBufferObject()
{
	clear();
}

void RenderBufferObject::create()
{
	glGenRenderbuffers(1, &handle);
}

void RenderBufferObject::clear()
{
	glDeleteRenderbuffers(1, &handle);
}

