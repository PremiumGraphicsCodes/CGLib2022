#include "EmitterSceneCreateCommand.h"

#include "../CrystalPhysics/MVP/MVPFluidEmitterScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "EmitterSceneCreateCommand";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string EmitterSceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

EmitterSceneCreateCommand::Args::Args()
{
}

EmitterSceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, 0)
{
	add(&newId);
}

EmitterSceneCreateCommand::EmitterSceneCreateCommand() :
	ICommand(&args, &results)
{}

bool EmitterSceneCreateCommand::execute(World* world)
{
	auto fluidScene = new MVPFluidEmitterScene(world->getNextSceneId(), "");
	world->getScenes()->addScene(fluidScene);
	results.newId.setValue(fluidScene->getId());
	return true;
}