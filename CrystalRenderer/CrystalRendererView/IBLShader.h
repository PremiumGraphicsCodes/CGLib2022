#pragma once

#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Shader/FrameBufferObject.h"
#include "Crystal/Shader/RenderBufferObject.h"

#include "CrystalRenderer/CrystalRenderer/IrradianceRenderer.h"
#include "CrystalRenderer/CrystalRenderer/IBLDiffuseRenderer.h"
#include "CrystalRenderer/CrystalRenderer/IBLSpecularRenderer.h"
#include "CrystalRenderer/CrystalRenderer/CubeMapRenderer.h"
#include "CrystalRenderer/CrystalRenderer/IScreenRenderer.h"
#include "CrystalRenderer/CrystalRenderer/SkyBoxRenderer.h"
#include "CrystalRenderer/CrystalRenderer/BRDFLUTRenderer.h"
#include "CrystalRenderer/CrystalRenderer/ImportanceRenderer.h"

namespace Crystal {
	namespace UI {

class IBLShader : public Renderer::IScreenRenderer
{
public:
	Shader::ShaderBuildStatus build() override;

	void render(const Graphics::Camera& camera, const int width, const int height) override;

private:
	struct Renderers
	{
		Renderer::CubeMapRenderer cubeMapRenderer;
		Renderer::IrradianceRenderer irradianceRenderer;
		Renderer::IBLDiffuseRenderer diffuseRenderer;
		Renderer::IBLSpecularRenderer specularRenderer;
		Renderer::BRDFLUTRenderer brdfLutRenderer;
		Renderer::ImportanceRenderer importanceRenderer;
		Renderer::SkyBoxRenderer skyBoxRenderer;
	};


	struct Textures
	{
		Shader::CubeMapTextureObject cubeMapTex;
		Shader::CubeMapTextureObject irradianceTex;
		Shader::CubeMapTextureObject importanceTex;
		Shader::TextureObject hdrTex;
		Shader::TextureObject brdfLutTex;
	};

	struct Buffers
	{
		Shader::FrameBufferObject fbo;
		Shader::RenderBufferObject rbo;
		Shader::VertexBufferObject positionVBO;
		Shader::VertexBufferObject normalVBO;
	};

	Renderers renderers;
	Textures textures;
	Buffers buffers;
	
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
	std::vector<unsigned int> indices;
};

	}

}