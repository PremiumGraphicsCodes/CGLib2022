#pragma once

#include "CrystalScene/Scene/IShader.h"
#include "Crystal/Graphics/Camera.h"
#include "Crystal/Shader/GLObjectFactory.h"
#include "CrystalPBR/CrystalPBR/SkyBoxRenderer.h"

namespace Crystal {
	namespace UI {

		class CubeMapShader
		{
		public:
			Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory);

			void release(Shader::GLObjectFactory& factory);

			void render(const Graphics::Camera& camera, const int width, const int height);

		private:
			Shader::SkyBoxRenderer skyBoxRenderer;
			Shader::CubeMapTextureObject* cubeMapTexture;
		};
	}

}