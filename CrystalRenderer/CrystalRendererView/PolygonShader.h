#pragma once

#include "CrystalScene/Scene/IShader.h"
#include "Crystal/Graphics/Camera.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "Crystal/Shader/FrameBufferObject.h"
#include "Crystal/Shader/TextureObject.h"
#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Graphics/Buffer2d.h"

#include "CrystalRenderer/CrystalRenderer/DFAlbedoRenderer.h"
#include "CrystalRenderer/CrystalRenderer/DFGeometryRenderer.h"
#include "CrystalRenderer/CrystalRenderer/DFLightRenderer.h"

namespace Crystal {
	namespace UI {

class PolygonShader //: public Scene::IShader
{
public:
	Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory); //override;

	void render(const Graphics::Camera& camera, const int width, const int height); //override;

private:
	Renderer::DFAlbedoRenderer albedoRenderer;
	Renderer::DFGeometryRenderer gRenderer;
	Renderer::DFLightRenderer lightRenderer;

	std::unique_ptr<Shader::TextureObject> colorTexture;
	std::unique_ptr<Shader::TextureObject> polygonTexture;
	std::unique_ptr<Shader::TextureObject> positionTexture;
	std::unique_ptr<Shader::TextureObject> normalTexture;
	std::unique_ptr<Shader::TextureObject> shadedTexture;
	std::unique_ptr<Shader::FrameBufferObject> fbo;
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer2d<float> texCoords;
	Graphics::Buffer3d<float> normals;
};

	}
}