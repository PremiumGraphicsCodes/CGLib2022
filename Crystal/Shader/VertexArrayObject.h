#pragma once

#include "glew.h"

namespace Crystal {
	namespace Shader {

class VertexArrayObject
{
public:
	VertexArrayObject();

	~VertexArrayObject();

	void build();

	void release();

	void bind();

	void unbind();

private:
	GLuint handle;

};
	}
}