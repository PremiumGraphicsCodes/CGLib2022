#pragma once

#include "IRenderer.h"

#include "CubeMapTextureObject.h"
#include <string>

namespace Crystal {
	namespace Shader {

class SkyBoxRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		CubeMapTextureObject cubeMapTexture;
	};

	SkyBoxRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void render(const Buffer& buffer);

	std::string getName() const override { return "SkyBoxRenderer"; }

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}