#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Renderer {

class DFAlbedoRenderer : public IRenderer
{
public:
	struct Buffer
	{
		struct FaceGroup {
			Shader::TextureObject* texture;
			std::vector<unsigned int> indices;
		};

		Shader::VertexBufferObject position;
		Shader::VertexBufferObject texCoord;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		std::vector<FaceGroup> faceGroups;
	};

	DFAlbedoRenderer();

	virtual void link() override;

	virtual void render() override;

	Buffer buffer;
private:
};

	}
}