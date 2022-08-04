#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/IRenderer.h"

namespace Crystal {
	namespace Shader {

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

	ShaderBuildStatus build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render(const Buffer& buffer);

	std::string getName() const override { return "PBLightRenderer"; }

private:
	Shader::ShaderObject* shader;
};

	}
}