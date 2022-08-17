#pragma once

#include "IRenderer.h"

#include "Crystal/Shader/CubeMapTextureObject.h"
#include "Crystal/Shader/VertexBufferObject.h"

namespace Crystal {
	namespace Renderer {

class ImportanceRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::CubeMapTextureObject* evnMapTex;
		Shader::VertexBufferObject* positions;
		float roughness;
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df viewMatrix;
		std::vector<unsigned int> indices;
	};

	ImportanceRenderer();

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}