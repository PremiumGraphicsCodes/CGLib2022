#pragma once

#include "glew.h"

#include "IGLObject.h"

namespace Crystal {
	namespace Shader {

class ITextureObject : public IGLObject
{
public:
	ITextureObject() : 
		IGLObject()
	{}

	virtual ~ITextureObject()
	{}

	virtual void bind(const int slotNumber) const = 0;

	virtual void unbind() const = 0;

	GLuint getHandle() const { return handle; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }

protected:
	GLuint handle;
	int width;
	int height;
};

	}
}