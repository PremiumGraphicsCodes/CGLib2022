#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/CubeMapTextureObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Renderer {

class IBLDiffuseRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::CubeMapTextureObject* irradianceMapTex;
	};

	IBLDiffuseRenderer();

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}