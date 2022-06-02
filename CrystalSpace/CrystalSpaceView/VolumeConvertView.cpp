#include "VolumeConvertView.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "../CrystalSpace/VolumeConvertAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

VolumeConvertView::VolumeConvertView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleSystemSelectView("ParticleSystem", model, canvas, ParticleSystemScene::getTypeName()),
	searchRadiusView("SearchRadius", 1.0)
{
	add(&particleSystemSelectView);
	add(&searchRadiusView);
}

void VolumeConvertView::onOk()
{
	auto id = particleSystemSelectView.getId();
	auto particleSystem = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);

	//Math::Box3d box;
	//Volume volume(32, 32, 32, box);

	//VolumeConvertAlgo converter;
	//converter.convert(volume, particleSystem.getShape(),);

	/*
	const auto& particles = volume.toParticles();
	std::vector<Vector3dd> positions;
	for (const auto& p : particles) {
		positions.push_back(p.getPosition());
	}
	ParticleAttribute attr;
	attr.color = glm::vec4(1, 0, 0, 0);
	attr.size = 1.0;
	getWorld()->getObjectFactory()->createParticleSystemScene(positions, attr, "VolumeConvert");
	getWorld()->updateViewModel();
	*/
}
