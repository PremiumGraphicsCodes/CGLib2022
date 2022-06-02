#pragma once

#include "CrystalScene/Scene/IScene.h"
#include "Voxel.h"
#include "VoxelPresenter.h"

#include <memory>

namespace Crystal {
	namespace Space {
		//class SparseVolumePresenter;

class VoxelScene : public Scene::IScene
{
public:
	VoxelScene(const int id, const std::string& name, std::unique_ptr<Voxel> shape);

	Voxel* getShape() const { return shape.get(); }

	void resetShape(std::unique_ptr<Voxel> shape) { this->shape = std::move(shape); }

	Scene::SceneType getType() const { return Scene::SceneType("VoxelScene"); }

	Scene::IPresenter* getPresenter() { return presenter.get(); }

	Math::Box3dd getBoundingBox() const override;

private:
	std::unique_ptr<Voxel> shape;
	std::unique_ptr<VoxelPresenter> presenter;
};

	}
}