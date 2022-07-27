#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/IRenderer.h"
#include "Crystal/Math/Matrix3d.h"

namespace Crystal {
	namespace Shader {

class DFLightRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::TextureObject* positionTex;
		Shader::TextureObject* normalTex;
		Shader::TextureObject* albedoTex;
	};

	DFLightRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render(const Buffer& buffer);

	std::string getName() const override { return "DFLightRenderer"; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}