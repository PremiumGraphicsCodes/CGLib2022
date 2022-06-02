#pragma once

#include <vector>
#include "glew.h"

namespace Crystal {
	namespace Shader {

class VertexBufferObject
{
public:
	VertexBufferObject();

	~VertexBufferObject();

	void build();

	void release();

	void send(const std::vector<int>& values);

	void send(const std::vector<float>& values);

	GLuint getHandle() const { return handle; }

	void bind() const;

	void unbind() const;

	bool operator==(const VertexBufferObject& rhs) const {
		return this->handle == rhs.handle;
	}

private:
	GLuint handle;
};

	}
}
