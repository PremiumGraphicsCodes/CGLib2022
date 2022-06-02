#include "VDBSceneVolumeToMeshCommand.h"

using namespace Crystal::VDB;

#include "../CrystalVDB/VDBMeshScene.h"
#include "../CrystalVDB/VDBPolygonMeshConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/VDBScene.h"
#include "../CrystalVDB/VDBVolumeToMeshConverter.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneVolumeToMesh";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
	PublicLabel ThresholdLabel = "Threshold";
	PublicLabel AdaptivityLabel = "Adaptivity";

	PublicLabel NewSceneIdLabel = "NewSceneId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneVolumeToMeshCommand::Args::Args() :
	vdbSceneId(::VDBSceneIdLabel, -1),
	threshold(::ThresholdLabel, 0.0),
	adaptivity(::AdaptivityLabel, 0.0)
{
	add(&vdbSceneId);
	add(&threshold);
	add(&adaptivity);
}

VDBSceneVolumeToMeshCommand::Results::Results() :
	newSceneId(::NewSceneIdLabel, -1)
{
	add(&newSceneId);
}

VDBSceneVolumeToMeshCommand::VDBSceneVolumeToMeshCommand() :
	ICommand(&args, &results)
{}

VDBSceneVolumeToMeshCommand::VDBSceneVolumeToMeshCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneVolumeToMeshCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneVolumeToMeshCommand::execute(World* world)
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
	for (auto v : volumes) {
		auto mesh = VDBVolumeToMeshConverter::toMesh(*v, args.threshold.getValue(), args.adaptivity.getValue());
		newScene->add(mesh);
	}
	world->addScene(newScene);
	results.newSceneId.setValue(newScene->getId());
	return true;
}