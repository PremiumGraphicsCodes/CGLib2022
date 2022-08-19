#pragma once

#include "IGLObject.h"
#include "glew.h"

namespace Crystal {
	namespace Shader {

class RenderBufferObject : public IGLObject
{
public:
	~RenderBufferObject();

	void create();

	void clear() override;

	GLuint getHandle() const { return handle; }

private:
	GLuint handle;
};
	}
}