#include "ISVAddView.h"

#include "../CrystalSpace/SparseVolumeScene.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

ISVAddView::ISVAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	nameView("Name", "SparseVolume01"),
	presenterView("Presenter"),
	colorMapView("ColorMap")
{
	add(&nameView);
	add(&presenterView);
	add(&colorMapView);
}

void ISVAddView::addVolume(std::unique_ptr<SparseVolumef> volume)
{
	auto scene = new SparseVolumeScene(getWorld()->getNextSceneId(), nameView.getValue(), std::move(volume));
	getWorld()->getScenes()->addScene(scene);

	auto presenter = scene->getPresenter();
	static_cast<SparseVolumePresenter*>(presenter)->setColorMap(colorMapView.getValue());
	presenter->createView(getWorld()->getRenderer());
}
