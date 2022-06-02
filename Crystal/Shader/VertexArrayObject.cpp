#include "VertexArrayObject.h"
#include <cassert>

using namespace Crystal::Shader;

VertexArrayObject::VertexArrayObject() :
	handle(0)
{
}

VertexArrayObject::~VertexArrayObject()
{
	//release();
}

void VertexArrayObject::build()
{
	assert(handle == 0);
	glGenVertexArrays(1, &handle);
}

void VertexArrayObject::release()
{
	if (handle != 0) {
		glDeleteVertexArrays(1, &handle);
	}
}

void VertexArrayObject::bind()
{
	assert(handle != 0);
	glBindVertexArray(handle);
}

void VertexArrayObject::unbind()
{
	glBindVertexArray(0);
}
