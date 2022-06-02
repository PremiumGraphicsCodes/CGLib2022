#pragma once

#include "../Shader/GLObjectFactory.h"
#include "../Shader/ShaderObject.h"
#include "../Shader/ShaderBuildStatus.h"

namespace Crystal {
	namespace Shader {

class IRenderer
{
public:
	IRenderer() {}

	virtual ~IRenderer() {}

	virtual ShaderBuildStatus build(Shader::GLObjectFactory& factory) = 0;

	virtual void release(Shader::GLObjectFactory& factory) = 0;

	virtual std::string getName() const = 0;
	//virtual void onRender() = 0;
};

	}
}