
#pragma once

#include "CrystalScene/Scene/IPresenter.h"
#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/LineShaderScene.h"

namespace Crystal {
	namespace Physics {
		class CSGBoundaryScene;

class CSGBoundaryScenePresenter : public Scene::IPresenter
{
public:
	explicit CSGBoundaryScenePresenter(CSGBoundaryScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override {};

	void updateView() override;

private:
	CSGBoundaryScene* model;
	Scene::LineShaderScene* view;
};

	}
}