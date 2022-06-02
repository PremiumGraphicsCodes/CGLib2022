#pragma once

#include "CrystalSpace/CrystalSpace/SparseVolumeScene.h"
#include "FluidVolumePresenter.h"

namespace Crystal {
	namespace Physics {

class FluidVolumeScene : public Scene::IScene
{
public:
	FluidVolumeScene(const int id, const std::string& name, std::unique_ptr<Space::SparseVolumef> shape);

	virtual ~FluidVolumeScene();

	Space::SparseVolumef* getShape() const { return shape.get(); }

	void resetShape(std::unique_ptr<Space::SparseVolumef> shape) { this->shape = std::move(shape); }

	Scene::SceneType getType() const { return Scene::SceneType("FluidVolumeScene"); }

	Scene::IPresenter* getPresenter() { return presenter.get(); }

	Math::Box3dd getBoundingBox() const override;


private:
	std::unique_ptr<FluidVolumePresenter> presenter;
	std::unique_ptr<Space::SparseVolumef> shape;
};


	}
}