#pragma once

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Matrix4d.h"

#include "Crystal/Shader/VertexBufferObject.h"
#include "Crystal/Graphics/Camera.h"

#include "LineBuffer.h"
#include "Crystal/Shader/LineRenderer.h"

#include "IShaderScene.h"

namespace Crystal {
	namespace Scene {
		class CameraShaderScene;

class LineShaderScene : public IShaderScene
{
public:
	explicit LineShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render(const Graphics::Camera& camera) override;

	void send(const LineBuffer& buffer);

	void setShader(Shader::LineRenderer* shader) { this->shader = shader; }

private:
	Shader::LineRenderer* shader;
	Shader::LineRenderer::Buffer sBuffer;
};

	}
}