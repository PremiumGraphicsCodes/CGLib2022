#pragma once

#include "../../CrystalScene/Scene/IPresenter.h"
#include "../../Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
	}
	namespace VDB {
		class VDBVolumeScene;

class VDBVolumePresenter : public Scene::IPresenter
{
public:
	explicit VDBVolumePresenter(VDBVolumeScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	VDBVolumeScene* model;
	Scene::PointShaderScene* view;
	Graphics::ColorMap colorMap;
};

	}
}