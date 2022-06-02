#pragma once

#include "CrystalScene/Scene/IPresenter.h"

#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class MPSFluidScene;

class MPSFluidSceneController : public Scene::IPresenter
{
public:
	explicit MPSFluidSceneController(MPSFluidScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override {};

	void updateView() override;

private:
	MPSFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}