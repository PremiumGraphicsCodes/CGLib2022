#include "FluidSceneUpdateCommand.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"

#include "../CrystalPhysics/MVP/MVPFluidScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "FluidSceneUpdateCommand";
	PublicLabel IdLabel = "Id";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
	PublicLabel ParticleRadiusLabel = "ParticleRadius";
	PublicLabel StiffnessLabel = "Stiffness";
	PublicLabel ViscosityLabel = "Viscosity";
	PublicLabel DensityLabel = "Density";
	PublicLabel TemperatureLabel = "Temperature";
	PublicLabel HeatDiffuseCoeLabel = "HeatDiffuseCoe";
	PublicLabel DragForceCoeLabel = "DragForceCoe";
	PublicLabel DragHeatCoeLabel = "DragHeatCoe";
	PublicLabel LifeLimitLabel = "LifeLimit";
	PublicLabel IsBoundary = "IsBoundary";
	PublicLabel NameLabel = "Name";
}


using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string FluidSceneUpdateCommand::getName()
{
	return ::CommandNameLabel;
}

FluidSceneUpdateCommand::Args::Args() :
	id(::IdLabel, -1),
	particleSystemId(::ParticleSystemIdLabel, -1),
	particleRadius(::ParticleRadiusLabel, 0.5f),
	stiffness(::StiffnessLabel, 1.0f),
	density(::DensityLabel, 1.0f),
	viscosity(::ViscosityLabel, 1.0f),
	temperature(::TemperatureLabel, 300.0f),
	heatDiffuseCoe(::HeatDiffuseCoeLabel, 1.0f),
	dragForceCoe(::DragForceCoeLabel, 0.0f),
	dragHeatCoe(::DragHeatCoeLabel, 0.0f),
	lifeLimit(::LifeLimitLabel, -1),
	isBoundary(::IsBoundary, false),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&id);
	add(&particleSystemId);
	add(&particleRadius);
	add(&stiffness);
	add(&density);
	add(&viscosity);
	add(&temperature);
	add(&heatDiffuseCoe);
	add(&isBoundary);
	add(&name);
	add(&dragForceCoe);
	add(&dragHeatCoe);
	add(&lifeLimit);
}

FluidSceneUpdateCommand::Results::Results()
{
}

FluidSceneUpdateCommand::FluidSceneUpdateCommand() :
	ICommand(&args, &results)
{}

FluidSceneUpdateCommand::FluidSceneUpdateCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &this->results)
{}

bool FluidSceneUpdateCommand::execute(World* world)
{
	auto fluidScene = world->getScenes()->findSceneById<MVPFluidScene*>(args.id.getValue());

	fluidScene->clearParticles();
	fluidScene->clear();

	fluidScene->setName(args.name.getValue());
	fluidScene->setPressureCoe(args.stiffness.getValue());
	fluidScene->setViscosityCoe(args.viscosity.getValue());
	fluidScene->setBoundary(args.isBoundary.getValue());
	fluidScene->setHeatDiffuseCoe(args.heatDiffuseCoe.getValue());
	fluidScene->setDragForceCoe(args.dragForceCoe.getValue());
	fluidScene->setDragHeatCoe(args.dragHeatCoe.getValue());
	fluidScene->setLifeLimit(args.lifeLimit.getValue());

	const auto psId = args.particleSystemId.getValue();
	if (psId > 0) {
		auto particles = world->getScenes()->findSceneById<IParticleSystemScene*>(psId);
		if (particles == nullptr) {
			return false;
		}
		const auto& positions = particles->getPositions();
		const auto radius = args.particleRadius.getValue();
		const auto density = args.density.getValue();
		const auto temperature = args.temperature.getValue();
		for (const auto& p : positions) {
			auto mp = fluidScene->create(p, radius, 0.25f, temperature);
			fluidScene->addParticle(mp);
		}
	}

	return true;
}