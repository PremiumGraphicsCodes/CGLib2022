#include "VolumeToPSView.h"

#include "../CrystalVDB/VDBPointsScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeToPointsConverter.h"

#include <iostream>

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VolumeToPSView::VolumeToPSView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	vdbVolumeSelectView("VDBVolume", model, canvas)
{
	add(&vdbVolumeSelectView);
}

void VolumeToPSView::onOk()
{
	const auto id = vdbVolumeSelectView.getId();
	auto volume = getWorld()->getScenes()->findSceneById<VDBVolumeScene*>(id);

	auto ps = VDBVolumeToPointsConverter::toPoints(*volume);
	ps->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(ps);
}