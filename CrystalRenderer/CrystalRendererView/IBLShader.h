#pragma once

#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Shader/FrameBufferObject.h"

#include "CrystalRenderer/CrystalRenderer/IrradianceRenderer.h"
#include "CrystalRenderer/CrystalRenderer/IBLDiffuseRenderer.h"
#include "CrystalRenderer/CrystalRenderer/CubeMapRenderer.h"
#include "CrystalRenderer/CrystalRenderer/IScreenRenderer.h"
#include "CrystalRenderer/CrystalRenderer/SkyBoxRenderer.h"

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
	Renderer::IBLDiffuseRenderer diffuseRenderer;
	Renderer::SkyBoxRenderer skyBoxRenderer;

	Shader::FrameBufferObject fbo;
	Shader::CubeMapTextureObject cubeMapTex;
	Shader::CubeMapTextureObject irradianceTex;
	Shader::TextureObject hdrTex;
	
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
	Shader::VertexBufferObject positionVBO;
	Shader::VertexBufferObject normalVBO;
	std::vector<unsigned int> indices;
};

	}

}