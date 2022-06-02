#pragma once

#include "VertexBufferObject.h"

#include "IRenderer.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shader {

class LineRenderer : IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject* position;
		Shader::VertexBufferObject* color;
		std::vector<unsigned int> indices;
		Math::Matrix4df projectionMatrix;
		Math::Matrix4df modelViewMatrix;
		GLfloat lineWidth;
	};
	//Shader::VertexArrayObject vao;

	LineRenderer();

	ShaderBuildStatus build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void render(const Buffer& buffer);

	std::string getName() const override { return "LineRenderer"; }

private:
	std::string getBuiltInVsSource() const;

	std::string getBuiltInFsSource() const;

	Shader::ShaderObject* shader;
};

	}
}