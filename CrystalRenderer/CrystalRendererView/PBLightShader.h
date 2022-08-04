#pragma once

#include "Crystal/Graphics/Camera.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Graphics/Buffer2d.h"
#include "CrystalRenderer/CrystalRenderer/PBLightRenderer.h"
#include "Crystal/Shader/ShaderBuildStatus.h"
#include "CrystalRenderer/CrystalRenderer/IScreenRenderer.h"

namespace Crystal {
	namespace UI {

class PBLightShader : public Renderer::IScreenRenderer
{
public:
	Shader::ShaderBuildStatus build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	Renderer::PBLightRenderer renderer;
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
};

	}

}