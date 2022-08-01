#pragma once

#include "CrystalScene/Scene/IShader.h"
#include "Crystal/Graphics/Camera.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "CrystalScene/Scene/PolygonRenderer.h"
#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Graphics/Buffer2d.h"
#include "CrystalPBR/CrystalPBR/DFGeometryRenderer.h"
#include "CrystalPBR/CrystalPBR/DFLightRenderer.h"

namespace Crystal {
	namespace UI {

		class PolygonShader //: public Scene::IShader
		{
		public:
			Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory); //override;

			void release(Shader::GLObjectFactory& factory); //override;

			void render(const Graphics::Camera& camera); //override;

			Shader::TextureObject* getTexture();// override;

		private:
			Shader::PolygonRenderer renderer;
			Shader::DFGeometryRenderer gRenderer;
			Shader::DFGeometryRenderer::Buffer gBuffer;
			Shader::DFLightRenderer lightRenderer;
			Shader::DFLightRenderer::Buffer lightBuffer;
			Shader::TextureObject* colorTexture;
			Shader::TextureObject* polygonTexture;
			Shader::TextureObject* geometryTexture;
			Shader::TextureObject* normalTexture;
			Shader::TextureObject* shadedTexture;
			Shader::FrameBufferObject* fbo;
			Graphics::Buffer3d<float> positions;
			Graphics::Buffer2d<float> texCoords;
			Graphics::Buffer3d<float> normals;
			Shader::PolygonRenderer::Buffer buffer;

			//			Shader::CubeMapTextureObject* cubeMapTexture;
		};
	}

}