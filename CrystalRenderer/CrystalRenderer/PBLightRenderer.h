#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Renderer {

class PBLightRenderer : public IRenderer
{
public:
	struct Buffer
	{
		Shader::VertexBufferObject position;
		Shader::VertexBufferObject normal;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelMatrix;
		Math::Matrix4dd viewMatrix;
		Math::Vector3df eyePosition;

		Math::Vector3df albedo;
		float metalic;
		float roughness;
		float ao;

		Math::Vector3df lightPosition;
		Math::Vector3df lightColor;

		std::vector<unsigned int> indices;
	};

	PBLightRenderer();

	void setShader(std::unique_ptr<Shader::ShaderObject> shader) override;

	void render() override;

	Buffer buffer;

private:
	std::unique_ptr<Shader::ShaderObject> shader;
};

	}
}