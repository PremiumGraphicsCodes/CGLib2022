#include "SparseVolumeScene.h"

#include "SparseVolumePresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

SparseVolumeScene::SparseVolumeScene(const int id, const std::string& name, std::unique_ptr<SparseVolumef> shape) :
	IScene(id, name),
	shape(std::move(shape))
{
	presenter = std::make_unique<SparseVolumePresenter>(this);
}

Box3dd SparseVolumeScene::getBoundingBox() const
{
	return shape->getBoundingBox();
}