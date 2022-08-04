#pragma once

#include "IRenderer.h"

#include "Crystal/Math/Matrix4d.h"
#include "Crystal/Shader/TextureObject.h"
#include <string>
#include <memory>

namespace Crystal {
	namespace Renderer {

class CubeMapRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		Shader::TextureObject* texture;
	};

	CubeMapRenderer();

	explicit CubeMapRenderer(std::unique_ptr<Shader::ShaderObject> shader) :
		IRenderer(std::move(shader))
	{}

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}