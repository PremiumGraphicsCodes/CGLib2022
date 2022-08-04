#pragma once

#include "Crystal/Shader/ShaderBuildStatus.h"
#include "Crystal/Graphics/Camera.h"

namespace Crystal {
	namespace Renderer {

class IScreenRenderer
{
public:
	virtual ~IScreenRenderer() = default;

	virtual Shader::ShaderBuildStatus build() = 0;

	virtual void render(const Graphics::Camera& camera, const int width, const int height) = 0;
};

	}
}