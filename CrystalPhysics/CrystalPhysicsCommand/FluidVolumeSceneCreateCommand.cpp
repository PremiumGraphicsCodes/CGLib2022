#include "FluidVolumeSceneCreateCommand.h"

#include "../CrystalPhysics/FluidVolumeScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "FluidVolumeSceneCreateCommand";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidVolumeSceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

FluidVolumeSceneCreateCommand::Args::Args()
{
}

FluidVolumeSceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, 0)
{
	add(&newId);
}

FluidVolumeSceneCreateCommand::FluidVolumeSceneCreateCommand() :
	ICommand(&args, &results)
{}

bool FluidVolumeSceneCreateCommand::execute(World* world)
{
	auto volumeScene = new FluidVolumeScene(world->getNextSceneId(), "", std::make_unique<Space::SparseVolumef>());
	world->getScenes()->addScene(volumeScene);
	results.newId.setValue(volumeScene->getId());
	return true;
}