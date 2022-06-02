#pragma once

#include "IScene.h"
#include "Crystal/Graphics/Material.h"
#include "MaterialPresenter.h"
#include <memory>

namespace Crystal {
	namespace Scene {
		class TextureScene;

class MaterialScene : public IScene
{
public:
	MaterialScene(const int id, const std::string& name, std::unique_ptr<Graphics::Material> material);

	~MaterialScene() {};

	Graphics::Material* getMaterial() { return material.get(); }

	SceneType getType() const override { return SceneTypeLabels::MaterialScene; }

	IPresenter* getPresenter() override { return presenter.get(); }
	
private:
	std::unique_ptr<Graphics::Material> material;
	std::unique_ptr<MaterialPresenter> presenter;
};

	}
}