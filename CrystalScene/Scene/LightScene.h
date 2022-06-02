#pragma once

#include "IScene.h"
#include "Crystal/Graphics/ColorRGBA.h"
#include "Crystal/Graphics/PointLight.h"
#include "LightPresenter.h"

namespace Crystal {
	namespace Scene {

class LightScene : public IScene
{
public:
	LightScene(const int id, const std::string& name, std::unique_ptr<Graphics::PointLight> light);

	~LightScene() {};

	Graphics::PointLight* getLight() const { return light.get(); }

	SceneType getType() const override { return SceneTypeLabels::LightScene; }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::unique_ptr<Graphics::PointLight> light;
	std::unique_ptr<LightPresenter> presenter;
};

	}
}