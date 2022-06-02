#pragma once

#include "IRenderer.h"

#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "GLObjectFactory.h"
#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"
#include <string>

namespace Crystal {
	namespace Shader {

class PointRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject size;
		Shader::VertexBufferObject color;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		int count = 0;
	};

	PointRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void render(const Buffer& buffer);

	void renderBlend(const Buffer& buffer);

	std::string getName() const override { return "PointRenderer"; }

private:
	std::string getBuiltInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Shader::ShaderObject* shader;
};

	}
}