#pragma once

#include "Crystal/Shader/IRenderer.h"

#include "Crystal/Shader/CubeMapTextureObject.h"
#include <string>

namespace Crystal {
	namespace Shader {

class CubeMapRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		CubeMapTextureObject* cubeMapTexture;
	};

	CubeMapRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void render(const Buffer& buffer);

	std::string getName() const override { return "CubeMapRenderer"; }

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}