#include "VoxelScene.h"

#include "VoxelPresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

VoxelScene::VoxelScene(const int id, const std::string& name, std::unique_ptr<Voxel> shape) :
	IScene(id, name),
	shape(std::move(shape))
{
	presenter = std::make_unique<VoxelPresenter>(this);
}

Box3dd VoxelScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}