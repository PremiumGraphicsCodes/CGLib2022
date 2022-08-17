#pragma once

#include "IRenderer.h"

namespace Crystal {
	namespace Renderer {

class ShadowRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
	};

	ShadowRenderer();

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}