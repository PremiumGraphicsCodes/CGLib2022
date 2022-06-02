#pragma once

#include "CrystalScene/Scene/IScene.h"
#include "VDBVolumeScene.h"
#include "VDBPointsScene.h"
#include "VDBMeshScene.h"

namespace Crystal {
	namespace VDB {

class VDBScene : public Scene::IScene
{
public:
	VDBScene() = default;

	VDBScene(const int id, const std::string& name) :
		Scene::IScene(id, name)
	{}

	void add(VDBVolumeScene* volume);

	void add(VDBPointsScene* points);

	void add(VDBMeshScene* mesh);

	Scene::SceneType getType() const override;

	Scene::IPresenter* getPresenter() override;

	std::vector<VDBVolumeScene*> getVolumes() const { return volumes; }

	std::vector<VDBPointsScene*> getPoints() const { return points; }

	std::vector<VDBMeshScene*> getMeshes() const { return meshes; }

private:
	std::vector<VDBVolumeScene*> volumes;
	std::vector<VDBPointsScene*> points;
	std::vector<VDBMeshScene*> meshes;
};
	}
}