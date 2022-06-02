#include "IVoxelAddView.h"

#include "../../Crystal/Shape/Volume.h"
#include "../Scene/VoxelScene.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

IVoxelAddView::IVoxelAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	nameView("Name", "Volume01"),
	presenterView("Presenter"),
	colorMapView("ColorMap")
{
	add(&nameView);
	add(&presenterView);
	add(&colorMapView);
}

void IVoxelAddView::addVoxel(std::unique_ptr<Volume<bool>> volume)
{
	auto scene = new VoxelScene(getWorld()->getNextSceneId(), nameView.getValue(), std::move(volume));
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	//static_cast<VolumePresenter*>(presenter)->setColorMap(colorMapView.getValue());
	presenter->createView(getWorld()->getRenderer());
}
