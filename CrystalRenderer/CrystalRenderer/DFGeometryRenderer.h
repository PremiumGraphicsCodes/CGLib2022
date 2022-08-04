#pragma once

#include "IRenderer.h"

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Math/Matrix3d.h"

namespace Crystal {
	namespace Renderer {

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

	void setShader(std::unique_ptr<Shader::ShaderObject> shader);

	void render() override;

	Buffer buffer;

private:
	std::unique_ptr<Shader::ShaderObject> shader;
};

	}
}