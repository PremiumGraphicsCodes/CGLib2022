#pragma once

#include "Crystal/Graphics/Camera.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Graphics/Buffer2d.h"
#include "CrystalRenderer/CrystalRenderer/PBLightRenderer.h"

namespace Crystal {
	namespace UI {

class PBLightShader //: public Scene::IShader
{
public:
	Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory); //override;

	void release(Shader::GLObjectFactory& factory); //override;

	void render(const Graphics::Camera& camera, const int width, const int height); //override;

private:
	Shader::PBLightRenderer renderer;
	Shader::PBLightRenderer::Buffer buffer;
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
};

	}

}