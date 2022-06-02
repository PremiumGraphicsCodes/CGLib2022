#include "VDBSceneVolumeToPointsCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneVolumeToPoints";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
	PublicLabel RadiusLabel = "Radius";

	PublicLabel NewSceneIdLabel = "NewSceneId";
}

#include "../CrystalVDB/VDBPointsScene.h"
#include "../CrystalVDB/VDBParticleSystemConverter.h"
#include "../CrystalVDB/VDBPolygonMeshConverter.h"
#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "../CrystalVDB/VDBVolumeToPointsConverter.h"
#include "../CrystalVDB/VDBScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneVolumeToPointsCommand::Args::Args() :
	vdbSceneId(::VDBSceneIdLabel, -1),
	radius(::RadiusLabel, 5.0)
{
	add(&vdbSceneId);
	add(&radius);
}

VDBSceneVolumeToPointsCommand::Results::Results() :
	newSceneId(::NewSceneIdLabel, -1)
{
	add(&newSceneId);
}

VDBSceneVolumeToPointsCommand::VDBSceneVolumeToPointsCommand() :
	ICommand(&args, &results)
{}

VDBSceneVolumeToPointsCommand::VDBSceneVolumeToPointsCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{
}

std::string VDBSceneVolumeToPointsCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneVolumeToPointsCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBScene*>(args.vdbSceneId.getValue());
	if (scene == nullptr) {
		return false;
	}
	const auto volumes = scene->getVolumes();
	if (volumes.empty()) {
		return false;
	}
	auto newScene = new VDBScene(world->getNextSceneId(), "");
	for (auto volume : volumes) {
		auto points = VDBVolumeToPointsConverter::toPoints(*volume);
		newScene->add(points);
	}
	world->addScene(newScene);
	results.newSceneId.setValue(newScene->getId());

	return true;
}
