#include "VDBScenePSToVolumeCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

#include "../CrystalVDB/VDBPointsScene.h"
#include "../CrystalVDB/VDBParticleSystemConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/SmoothVolumeConverter.h"
#include "../CrystalVDB/VDBScene.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBScenePSToVolume";
	PublicLabel SceneIdLabel = "SceneId";
	PublicLabel RadiusLabel = "Radius";
	PublicLabel VoxelSizeLabel = "VoxelSize";

	PublicLabel IsFlameLabel = "IsFlame";
	PublicLabel SmokeTemperatureLabel = "SmokeTemperature";
	PublicLabel FlameTemperatureLabel = "FlameTemperature";

	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBScenePSToVolumeCommand::Args::Args() :
	sceneId(::SceneIdLabel, -1),
	radius(::RadiusLabel, 5.0),
	voxelSize(::VoxelSizeLabel, 1.0),
	isFlame(::IsFlameLabel, false),
	smokeTemperature(::SmokeTemperatureLabel, 400.0f),
	flameTemperature(::FlameTemperatureLabel, 1000.0f)
{
	add(&sceneId);
	add(&radius);
	add(&voxelSize);
	add(&smokeTemperature);
	add(&flameTemperature);
}

VDBScenePSToVolumeCommand::Results::Results() :
	newSceneId(::NewIdLabel, -1)
{
}

VDBScenePSToVolumeCommand::VDBScenePSToVolumeCommand() :
	ICommand(&args, &results)
{}

VDBScenePSToVolumeCommand::VDBScenePSToVolumeCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBScenePSToVolumeCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBScenePSToVolumeCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBScene*>(args.sceneId.getValue());
	if (scene == nullptr) {
		return false;
	}
	auto newScene = new VDBScene(world->getNextSceneId(), "density");

	const auto points = scene->getPoints();
	if (args.isFlame.getValue()) {
		for (auto p : points) {
			SmoothVolumeConverter converter;
			auto volumes = converter.buildFlame(p, args.radius.getValue(), args.voxelSize.getValue(), args.smokeTemperature.getValue(), args.flameTemperature.getValue());
			for (auto v : volumes) {
				newScene->add(v);
			}
		}
	}
	else {
		for (auto p : points) {
			SmoothVolumeConverter converter;
			const auto names = p->getFloatAttributeNames();
			auto volumes = converter.build(p, args.radius.getValue(), args.voxelSize.getValue(), names);
			for (auto v : volumes) {
				newScene->add(v);
			}
		}
	}
	world->addScene(newScene);
	return true;
}
