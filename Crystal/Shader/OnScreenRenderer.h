#pragma once

#include "IRenderer.h"

#include "ShaderObject.h"
#include <memory>

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
		class ITextureObject;

class OnScreenRenderer : IRenderer
{
public:
	ShaderBuildStatus build(GLObjectFactory& factory) override;

	void release(GLObjectFactory& factory) override;

	void render(const ITextureObject& texture);

	std::string getName() const override { return "OnScreenRenderer"; }

private:
	std::string getBuildinVertexShaderSource();

	std::string getBuildinFragmentShaderSource();

	void findLocation();

private:
	ShaderObject* shader;
};

	}
}