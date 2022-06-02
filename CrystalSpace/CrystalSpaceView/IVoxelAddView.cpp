#include "IVoxelAddView.h"

#include "../CrystalSpace/VoxelScene.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

IVoxelAddView::IVoxelAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	nameView("Name", "Voxel01")
{
	add(&nameView);
}

void IVoxelAddView::addVoxel(std::unique_ptr<Voxel> voxel)
{
	auto scene = new VoxelScene(getWorld()->getNextSceneId(), nameView.getValue(), std::move(voxel));
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());
}
