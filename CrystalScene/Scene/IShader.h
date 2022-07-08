#pragma once

#include "Crystal/Shader/ShaderBuildStatus.h"

namespace Crystal {
	namespace Scene {

class IShader
{
public:
	virtual ~IShader() {}

	virtual Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory) = 0;

	virtual void release(Shader::GLObjectFactory& factory) = 0;

	virtual void render(const Graphics::Camera& camera) = 0;

	virtual Shader::TextureObject* getTexture() = 0;
};

	}
}