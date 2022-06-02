#pragma once

#include "../../CrystalScene/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene {
		class LineShaderScene;
	}
	namespace VDB {
		class VDBMeshScene;

class VDBMeshPresenter : public Scene::IPresenter
{
public:
	explicit VDBMeshPresenter(VDBMeshScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	VDBMeshScene* model;
	Scene::LineShaderScene* view;
};

	}
}