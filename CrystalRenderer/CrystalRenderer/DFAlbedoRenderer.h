#pragma once

#include "Crystal/Shader/ShaderObject.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Shader/IRenderer.h"

namespace Crystal {
	namespace Renderer {

class DFAlbedoRenderer : public Shader::IRenderer
{
public:
	struct Buffer
	{
		struct FaceGroup {
			Shader::TextureObject* texture;
			std::vector<unsigned int> indices;
		};

		Shader::VertexBufferObject position;
		Shader::VertexBufferObject texCoord;
		Math::Matrix4dd projectionMatrix;
		Math::Matrix4dd modelViewMatrix;
		std::vector<FaceGroup> faceGroups;
	};

	DFAlbedoRenderer();

	Shader::ShaderBuildStatus build(Shader::GLObjectFactory& glFactory) override;

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