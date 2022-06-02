#include "PhysicsSolverCreateCommand.h"

#include "../CrystalPhysics/MVP/MVPFluidSolver.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "PhysicsSolverCreateCommand";
	PublicLabel NewIdLabel = "NewId";
}


using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string PhysicsSolverCreateCommand::getName()
{
	return ::CommandNameLabel;
}

PhysicsSolverCreateCommand::Args::Args()
{
}

PhysicsSolverCreateCommand::Results::Results() :
	newId(::NewIdLabel, -1)
{
	add(&newId);
}

PhysicsSolverCreateCommand::PhysicsSolverCreateCommand() :
	ICommand(&args, &results)
{}

bool PhysicsSolverCreateCommand::execute(World* world)
{
	auto solver = new MVPFluidSolver(world->getNextSceneId());
	world->addAnimation(solver);

	results.newId.setValue(solver->getId());

	return true;
}
