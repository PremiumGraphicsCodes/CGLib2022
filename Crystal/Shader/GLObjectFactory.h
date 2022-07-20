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

	//template<class T>
	//T create()

	void add(IGLObject* object);

	void remove(IGLObject* object);

private:
	std::list<std::unique_ptr<IGLObject>> objects;
};

	}
}