#pragma once

#include "IRenderer.h"

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Math/Matrix3d.h"

namespace Crystal {
	namespace Renderer {

class DFLightRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::TextureObject* positionTex;
		Shader::TextureObject* normalTex;
		Shader::TextureObject* albedoTex;
		Math::Matrix4dd invModelViewMatrix;
		Math::Matrix4dd invProjectionMatrix;
		Math::Matrix3dd invNormalMatrix;
		Math::Vector3df lightPosition;
		Math::Vector3df lightColor;
	};

	DFLightRenderer();

	Shader::ShaderBuildStatus build() override;

	void render();

	Buffer buffer;

private:
	std::unique_ptr<Shader::ShaderObject> shader;
};

	}
}