#pragma once

namespace Crystal {
	namespace Graphics {
		struct Material;
		class PointLight;
	}
	namespace Shader {
		class TextureObject;
	}
	namespace Scene {
		class LightShaderScene;
		class MaterialShaderScene;
		class TextureShaderScene;

class IMaterialScene
{
public:
	virtual void setMaterialBuffer(MaterialShaderScene* buffer) = 0;

	virtual void sendMaterial(const int index, const Graphics::Material& material) = 0;

	virtual void sendAllMaterials() = 0;

	virtual void sendLight(const int index, const Graphics::PointLight& light) = 0;

	virtual void sendAllLights() = 0;

	virtual void sendTexture(const int index, const Shader::TextureObject& texture) = 0;

	virtual void sendAllTextures() = 0;
};

	}
}