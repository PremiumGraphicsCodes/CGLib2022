#include "FluidVolumeScene.h"

#include "FluidVolumePresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

FluidVolumeScene::FluidVolumeScene(const int id, const std::string& name, std::unique_ptr<SparseVolumef> shape) :
	IScene(id, name),
	shape(std::move(shape))
{
	presenter = std::make_unique<FluidVolumePresenter>(this);
}

FluidVolumeScene::~FluidVolumeScene()
{}

Box3dd FluidVolumeScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}