#pragma once

#include "CrystalScene/Scene/IPresenter.h"

#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class DFFluidScene;

class DFFluidSceneController : public Scene::IPresenter
{
public:
	explicit DFFluidSceneController(DFFluidScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override{};

	void updateView() override;

private:
	DFFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}