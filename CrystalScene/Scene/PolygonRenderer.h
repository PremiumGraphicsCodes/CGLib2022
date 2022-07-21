#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/IRenderer.h"

namespace Crystal {
	namespace Shader {

class PolygonRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject color;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		std::vector<unsigned int> indices;
	};

	PolygonRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render(const Buffer& buffer);

	std::string getName() const override { return "PolygonRenderer"; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}