#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/IRenderer.h"
#include "Crystal/Math/Matrix3d.h"

namespace Crystal {
	namespace Shader {

class DFGeometryRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject normal;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		Math::Matrix3dd normalMatrix;
		std::vector<unsigned int> indices;
	};

	DFGeometryRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render(const Buffer& buffer);

	std::string getName() const override { return "DFGeometryRenderer"; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}