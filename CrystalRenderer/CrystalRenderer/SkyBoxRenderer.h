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

	explicit SkyBoxRenderer(std::unique_ptr<Shader::ShaderObject> shader) :
		IRenderer(std::move(shader))
	{}

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}