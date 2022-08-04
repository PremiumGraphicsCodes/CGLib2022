#pragma once

#include "Crystal/Util/UnCopyable.h"
#include "Crystal/Shader/ShaderObject.h"
#include <memory>

namespace Crystal {
	namespace Renderer {

class IRenderer : private UnCopyable
{
public:
	IRenderer() = default;

	explicit IRenderer(std::unique_ptr<Shader::ShaderObject> shader) :
		shader(std::move(shader))
	{}

	virtual ~IRenderer() = default;

	void setShader(std::unique_ptr<Shader::ShaderObject> shader)
	{
		this->shader = std::move(shader);
	}

	virtual void link() = 0;

	virtual void render() = 0;

protected:
	std::unique_ptr<Shader::ShaderObject> shader;
};

	}
}