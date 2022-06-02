#include "PSToVolumeView.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/PolygonMeshScene.h"

#include "../CrystalVDB/VDBPointsScene.h"
#include "../CrystalVDB/VDBParticleSystemConverter.h"
#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"

#include <iostream>

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

PSToVolumeView::PSToVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleSystemSelectView("ParticleSystem", model, canvas),
	radiusView("Radius", 1.0),
	voxelSizeView("VoxelSize", 0.5)
{
	add(&particleSystemSelectView);
	add(&radiusView);
	add(&voxelSizeView);
}

void PSToVolumeView::onOk()
{
	auto id = particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (scene == nullptr) {
		return;
	}

	/*
	VDBParticleSystemScene ps;
	auto particles = scene->getShape()->getParticles();
	for (auto p : scene->getShape()->getParticles()) {
		ps.add(p->getPosition(), p->getAttribute().size);
	}

	VDBParticleSystemConverter converter;
	VDBVolumeScene* volume = new VDBVolumeScene();
	converter.toVolume(ps, radiusView.getValue(), voxelSizeView.getValue(), volume);
	std::cout << "voxels = " << volume->getActiveVoxelCount() << std::endl;;
	*/
}