#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Renderer {

class IrradianceRenderer : public IRenderer
{
public:
	struct Buffer
	{
	};

	IrradianceRenderer();

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}