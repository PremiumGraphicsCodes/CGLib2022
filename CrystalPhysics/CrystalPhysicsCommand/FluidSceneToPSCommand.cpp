#include "FluidSceneToPSCommand.h"

#include "../CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "FluidSceneToPSCommand";
	PublicLabel FluidIdLabel = "FluidId";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
}

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidSceneToPSCommand::getName()
{
	return ::CommandNameLabel;
}

FluidSceneToPSCommand::Args::Args() :
	fluidId(::FluidIdLabel, -1),
	particleSystemId(::ParticleSystemIdLabel, -1)
{
	add(&fluidId);
	add(&particleSystemId);
}

FluidSceneToPSCommand::Results::Results()
{
}

FluidSceneToPSCommand::FluidSceneToPSCommand() :
	ICommand(&args, &results)
{}

bool FluidSceneToPSCommand::execute(World* world)
{
	/*
	auto fluidScene = world->getScenes()->findSceneById<MVPFluidScene*>(args.fluidId.getValue());
	if (fluidScene == nullptr) {
		return false;
	}

	auto particleScene = world->getScenes()->findSceneById<ParticleSystemScene*>(args.particleSystemId.getValue());
	if (particleScene == nullptr) {
		return false;
	}
	auto& particles = particleScene->getShape()->getParticles();

	auto macroPositions = fluidScene->getParticles();
	for (int i = 0; i < macroPositions.size(); ++i) {
		particles[i]->moveTo(macroPositions[i]->getPosition());
	}
	*/

	return true;
}