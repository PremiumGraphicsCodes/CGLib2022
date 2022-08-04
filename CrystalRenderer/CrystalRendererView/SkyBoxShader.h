#pragma once

#include "CrystalScene/Scene/IShader.h"
#include "Crystal/Graphics/Camera.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "CrystalRenderer/CrystalRenderer/SkyBoxRenderer.h"

namespace Crystal {
	namespace UI {

class SkyBoxShader
{
public:
	Shader::ShaderBuildStatus build();

	void render(const Graphics::Camera& camera, const int width, const int height);

private:
	Renderer::SkyBoxRenderer skyBoxRenderer;
	std::unique_ptr<Shader::CubeMapTextureObject> cubeMapTexture;
};

	}

}