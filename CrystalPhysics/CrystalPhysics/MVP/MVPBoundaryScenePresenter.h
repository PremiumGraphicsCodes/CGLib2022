#pragma once

#include "CrystalScene/Scene/IPresenter.h"

#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class MVPBoundaryScene;

class MVPBoundaryScenePresenter : public Scene::IPresenter
{
public:
	explicit MVPBoundaryScenePresenter(MVPBoundaryScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override {};

	void updateView() override;

private:
	MVPBoundaryScene* model;
	Scene::PointShaderScene* view;
};

	}
}