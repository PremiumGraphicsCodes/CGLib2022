#pragma once

#include "../Util/UnCopyable.h"
#include "IGLObject.h"

#include <list>
#include <memory>

namespace Crystal {
	namespace Shader {
		class FrameBufferObject;
		class VertexBufferObject;
		class ShaderObject;
		class TextureObject;

class GLObjectFactory : private UnCopyable
{
public:
	~GLObjectFactory();

	void clear();

	FrameBufferObject* createFrameBufferObject();

	VertexBufferObject* createVertexBufferObject();

	ShaderObject* createShaderObject();

	TextureObject* createTextureObject();

	void remove(IGLObject* fbo);

private:
	std::list<std::unique_ptr<IGLObject>> objects;
};

	}
}