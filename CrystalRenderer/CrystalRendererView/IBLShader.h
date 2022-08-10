#pragma once

#include "CrystalRenderer/CrystalRenderer/IrradianceRenderer.h"
#include "Crystal/Shader/ShaderBuildStatus.h"
#include "CrystalRenderer/CrystalRenderer/CubeMapRenderer.h"
#include "CrystalRenderer/CrystalRenderer/IScreenRenderer.h"

namespace Crystal {
	namespace UI {

class IBLShader : public Renderer::IScreenRenderer
{
public:
	Shader::ShaderBuildStatus build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	Renderer::CubeMapRenderer cubeMapRenderer;
	Renderer::IrradianceRenderer irradianceRenderer;
	//Graphics::Buffer3d<float> positions;
	//Graphics::Buffer3d<float> normals;
};

	}

}