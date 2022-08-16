#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/CubeMapTextureObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Renderer {

class IrradianceRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::CubeMapTextureObject* cubeMapTex;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd viewMatrix;
	};

	IrradianceRenderer();

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}