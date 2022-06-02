#pragma once

#include "CrystalScene/Scene/IPresenter.h"
#include "../../Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
	}
	namespace Physics {
		class FluidVolumeScene;

class FluidVolumePresenter : public Scene::IPresenter
{
public:
	explicit FluidVolumePresenter(FluidVolumeScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override;

	void updateView() override;

	void setColorMap(const Graphics::ColorMap& colorMap) { this->colorMap = colorMap; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	Scene::PointShaderScene* view;
	FluidVolumeScene* model;
	Graphics::ColorMap colorMap;
};

	}
}