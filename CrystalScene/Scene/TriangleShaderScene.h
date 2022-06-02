#pragma once

#include "IShaderScene.h"
#include "TriangleBuffer.h"
#include "Crystal/Shader/TriangleRenderer.h"
#include "Crystal/Shader/VertexBufferObject.h"

#include <string>

namespace Crystal {
	namespace Scene {
		class TriangleShader;
		class CameraShaderScene;

class TriangleShaderScene : public IShaderScene
{
public:
	explicit TriangleShaderScene(const std::string& name) :
		IShaderScene(name)
	{}

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void send(const TriangleBuffer& buffer);

	void setShader(Shader::TriangleRenderer* shader);

	void render(const Graphics::Camera& camera) override;

private:
	std::string name;
	Shader::TriangleRenderer* shader;
	Shader::TriangleRenderer::Buffer sBuffer;
};

	}
}