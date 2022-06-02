#include "FluidSceneCreateCommand.h"

#include "../CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "FluidSceneCreateCommand";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidSceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

FluidSceneCreateCommand::Args::Args()
{
}

FluidSceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, 0)
{
	add(&newId);
}

FluidSceneCreateCommand::FluidSceneCreateCommand() :
	ICommand(&args, &results)
{}

bool FluidSceneCreateCommand::execute(World* world)
{
	auto fluidScene = new MVPFluidScene(world->getNextSceneId(), "");
	world->getScenes()->addScene(fluidScene);
	results.newId.setValue(fluidScene->getId());
	return true;
}