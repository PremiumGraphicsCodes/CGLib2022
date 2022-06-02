#pragma once

#include "IShaderScene.h"
#include "Crystal/Graphics/Material.h"
#include "Crystal/Graphics/PointLight.h"
#include "Crystal/Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {
		class IMaterialScene;

class MaterialShaderScene
{
public:
	void add(const Graphics::Material& material) { this->materials.push_back(material); }

	std::vector<Graphics::Material> getMaterials() const { return materials; }

	void updateMaterial(const int index);

	void add(const Graphics::PointLight& light) { this->lights.push_back(light); }

	std::vector<Graphics::PointLight> getLights() const { return lights; }

	void updateLight(const int index);

	void add(Shader::TextureObject* texture) { this->textures.push_back(texture); }

	std::vector<Shader::TextureObject*> getTextures() const { return textures; }

	void updateTexture(const int index);

	void addParent(IMaterialScene* parent) { this->parentScenes.push_back(parent); }

private:
	std::vector<Graphics::Material> materials;
	std::vector<Graphics::PointLight> lights;
	std::vector<Shader::TextureObject*> textures;
	std::list<IMaterialScene*> parentScenes;
};

	}
}