#pragma once

#include "Crystal/Util/UnCopyable.h"
#include "Crystal/Shader/ShaderBuildStatus.h"
#include "Crystal/Shader/ShaderObject.h"

namespace Crystal {
	namespace Renderer {

class IRenderer : private UnCopyable
{
public:
	virtual ~IRenderer() = default;

	virtual Shader::ShaderBuildStatus build() = 0;

	virtual void render() = 0;
};

	}
}