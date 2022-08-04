#pragma once

#include "CrystalScene/Scene/IShader.h"
#include "Crystal/Graphics/Camera.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "CrystalRenderer/CrystalRenderer/SkyBoxRenderer.h"
#include "CrystalRenderer/CrystalRenderer/IScreenRenderer.h"

namespace Crystal {
	namespace UI {

class SkyBoxShader : public Renderer::IScreenRenderer
{
public:
	Shader::ShaderBuildStatus build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	Renderer::SkyBoxRenderer skyBoxRenderer;
	std::unique_ptr<Shader::CubeMapTextureObject> cubeMapTexture;
};

	}
}