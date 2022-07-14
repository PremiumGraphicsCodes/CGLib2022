#pragma once

#include "CrystalScene/Scene/IShader.h"
#include "Crystal/Graphics/Camera.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/SkyBoxRenderer.h"

namespace Crystal{
	namespace UI {

class CubeMapShader : public Scene::IShader
{
public:
	Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void render(const Graphics::Camera& camera) override;

	Shader::TextureObject* getTexture() override;

private:
	Shader::SkyBoxRenderer skyBoxRenderer;
};
	}

}