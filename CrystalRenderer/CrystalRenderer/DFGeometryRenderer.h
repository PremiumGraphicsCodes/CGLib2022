#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/IRenderer.h"
#include "Crystal/Math/Matrix3d.h"

namespace Crystal {
	namespace Renderer {

class IRenderer
{
public:
	virtual Shader::ShaderBuildStatus build() = 0;

	virtual void render() = 0;
};

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

	Shader::ShaderBuildStatus build() override;

	void render() override;

	Buffer buffer;

private:
	std::unique_ptr<Shader::ShaderObject> shader;
};

	}
}