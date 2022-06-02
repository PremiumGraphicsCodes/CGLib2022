
#pragma once

#include "CrystalScene/Scene/IPresenter.h"
#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/LineShaderScene.h"

namespace Crystal {
	namespace Physics {
		class MeshBoundaryScene;

class MeshBoundaryScenePresenter : public Scene::IPresenter
{
public:
	explicit MeshBoundaryScenePresenter(MeshBoundaryScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override;

	void updateView() override;

private:
	MeshBoundaryScene* model;
	Scene::LineShaderScene* view;

	void updateScreenView();

};

	}
}