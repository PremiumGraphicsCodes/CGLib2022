#pragma once

#include "Crystal/Util/UnCopyable.h"
#include "Crystal/Shader/ShaderObject.h"
#include <memory>

namespace Crystal {
	namespace Renderer {

class IRenderer : private UnCopyable
{
public:
	virtual ~IRenderer() = default;

	virtual void setShader(std::unique_ptr<Shader::ShaderObject> shader) = 0;

	virtual void render() = 0;

};

	}
}