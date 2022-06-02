#include "PhysicsSolverUpdateCommand.h"

#include "../CrystalPhysics/MVP/MVPFluidSolver.h"
#include "../CrystalPhysics/MVP/MVPFluidScene.h"
#include "../CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "../CrystalPhysics/Boundary/CSGBoundaryScene.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "PhysicsSolverUpdateCommand";
	PublicLabel IdLabel = "Id";
	PublicLabel FluidSceneIdsLabel = "FluidSceneIds";
	PublicLabel EmitterSceneIdsLabel = "EmitterSceneIds";
	PublicLabel CSGBoundarySceneIdsLabel = "CSGBoundarySceneIds";
	PublicLabel EffectLengthLabel = "EffectLength";
	PublicLabel ExternalForceLabel = "ExternalForce";
	PublicLabel BuoyancyForceLabel = "BuoyancyForce";
	PublicLabel TimeStepLabel = "TimeStep";
	PublicLabel NameLabel = "Name";
}


using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string PhysicsSolverUpdateCommand::getName()
{
	return ::CommandNameLabel;
}

PhysicsSolverUpdateCommand::Args::Args() :
	id(::IdLabel, -1),
	fluidSceneIds(::FluidSceneIdsLabel, {}),
	emitterSceneIds(::EmitterSceneIdsLabel, {}),
	csgBoundarySceneIds(::CSGBoundarySceneIdsLabel, {}),
	effectLength(::EffectLengthLabel, 2.0f),
	externalForce(::ExternalForceLabel, Vector3df(0,-9.8f, 0.0)),
	buoyancyForce(::BuoyancyForceLabel, Vector3df(0,0,0)),
	timeStep(::TimeStepLabel, 0.03f),
	name(::NameLabel, std::string("FluidScene"))
{
	add(&id);
	add(&fluidSceneIds);
	add(&emitterSceneIds);
	add(&csgBoundarySceneIds);
	add(&effectLength);
	add(&externalForce);
	add(&buoyancyForce);
	add(&timeStep);
	add(&name);
}

PhysicsSolverUpdateCommand::Results::Results()
{
}

PhysicsSolverUpdateCommand::PhysicsSolverUpdateCommand() :
	ICommand(&args, &results)
{}

bool PhysicsSolverUpdateCommand::execute(World* world)
{
	auto solver = world->findAnimatorById<MVPFluidSolver*>(args.id.getValue());
	if (solver == nullptr) {
		return false;
	}

	solver->setEffectLength(args.effectLength.getValue());

	solver->clear();

	solver->setMaxTimeStep(args.timeStep.getValue());

	const auto ids = args.fluidSceneIds.getValue();

	for (const auto id : ids) {
		auto scene = world->getScenes()->findSceneById<MVPFluidScene*>(id);
		if (scene->isBoundary()) {
			solver->addBoundaryScene(scene);
		}
		else {
			solver->addFluidScene(scene);
		}
	}

	const auto emitterIds = args.emitterSceneIds.getValue();

	for (const auto id : emitterIds) {
		auto scene = world->getScenes()->findSceneById<MVPFluidEmitterScene*>(id);
		solver->addEmitterScene(scene);
	}

	const auto boundaryIds = args.csgBoundarySceneIds.getValue();
	for (const auto id : boundaryIds) {
		auto scene = world->getScenes()->findSceneById<CSGBoundaryScene*>(id);
		solver->addBoundary(scene);
	}

	solver->setExternalForce(args.externalForce.getValue());
	solver->setBuoyancy(args.buoyancyForce.getValue());

	solver->setupBoundaries();


	return true;
}
