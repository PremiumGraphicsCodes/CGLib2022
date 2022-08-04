#pragma once

#include "IRenderer.h"

#include "Crystal/Shader/CubeMapTextureObject.h"
#include <string>

namespace Crystal {
	namespace Renderer {

class SkyBoxRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		Shader::CubeMapTextureObject* cubeMapTexture;
	};

	SkyBoxRenderer();

	void setShader(std::unique_ptr<Shader::ShaderObject> shader) override;

	void render() override;

	Buffer buffer;

private:
	std::unique_ptr<Shader::ShaderObject> shader;
};

	}
}