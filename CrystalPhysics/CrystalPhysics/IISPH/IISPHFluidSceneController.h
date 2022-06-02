#pragma once

#include "CrystalScene/Scene/IPresenter.h"

#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class IISPHFluidScene;

class IISPHFluidSceneController : public Scene::IPresenter
{
public:
	explicit IISPHFluidSceneController(IISPHFluidScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override{};

	void updateView() override;

private:
	IISPHFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}