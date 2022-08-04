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

	explicit DFGeometryRenderer(std::unique_ptr<Shader::ShaderObject> shader) :
		IRenderer(std::move(shader))
	{}

	void link() override;

	void render() override;

	Buffer buffer;

private:
};

	}
}