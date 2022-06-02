#include "PhysicsCommandFactory.h"

#include "FluidSceneCreateCommand.h"
#include "FluidSceneUpdateCommand.h"
#include "EmitterSceneCreateCommand.h"
#include "EmitterSceneUpdateCommand.h"
#include "FluidSceneToPSCommand.h"
#include "FluidSimulationCommand.h"
#include "CSGBoundarySceneCreateCommand.h"
#include "CSGBoundarySceneUpdateCommand.h"
#include "MeshBoundarySceneCreateCommand.h"
#include "MeshBoundarySceneUpdateCommand.h"
#include "PhysicsSolverCreateCommand.h"
#include "PhysicsSolverUpdateCommand.h"
#include "PhysicsSolverExportCommand.h"
#include "SPHVolumeConvertCommand.h"
#include "MVPVolumeConvertCommand.h"
#include "FluidVolumeSceneCreateCommand.h"
#include "FluidVolumeExportCommand.h"

using namespace Crystal::Command;
using namespace Crystal::Physics;

std::unique_ptr<ICommand> PhysicsCommandFactory::create(const std::string& name)
{
	if (name == FluidSceneCreateCommand::getName()) {
		return std::make_unique<FluidSceneCreateCommand>();
	}
	else if (name == FluidSceneUpdateCommand::getName()) {
		return std::make_unique<FluidSceneUpdateCommand>();
	}
	else if (name == EmitterSceneCreateCommand::getName()) {
		return std::make_unique<EmitterSceneCreateCommand>();
	}
	else if (name == EmitterSceneUpdateCommand::getName()) {
		return std::make_unique<EmitterSceneUpdateCommand>();
	}
	else if (name == FluidSceneToPSCommand::getName()) {
		return std::make_unique<FluidSceneToPSCommand>();
	}
	else if (name == FluidSimulationCommand::getName()) {
		return std::make_unique<FluidSimulationCommand>();
	}
	else if (name == CSGBoundarySceneCreateCommand::getName()) {
		return std::make_unique<CSGBoundarySceneCreateCommand>();
	}
	else if (name == CSGBoundarySceneUpdateCommand::getName()) {
		return std::make_unique<CSGBoundarySceneUpdateCommand>();
	}
	else if (name == MeshBoundarySceneCreateCommand::getName()) {
		return std::make_unique<MeshBoundarySceneCreateCommand>();
	}
	else if (name == MeshBoundarySceneUpdateCommand::getName()) {
		return std::make_unique<MeshBoundarySceneUpdateCommand>();
	}
	else if (name == PhysicsSolverCreateCommand::getName()) {
		return std::make_unique<PhysicsSolverCreateCommand>();
	}
	else if (name == PhysicsSolverUpdateCommand::getName()) {
		return std::make_unique<PhysicsSolverUpdateCommand>();
	}
	else if (name == PhysicsSolverExportCommand::getName()) {
		return std::make_unique<PhysicsSolverExportCommand>();
	}
	else if (name == SPHVolumeConvertCommand::getName()) {
		return std::make_unique<SPHVolumeConvertCommand>();
	}
	else if (name == MVPVolumeConvertCommand::getName()) {
		return std::make_unique<MVPVolumeConvertCommand>();
	}
	else if (name == FluidVolumeSceneCreateCommand::getName()) {
		return std::make_unique<FluidVolumeSceneCreateCommand>();
	}
	else if (name == FluidVolumeExportCommand::getName()) {
		return std::make_unique<FluidVolumeExportCommand>();
	}
	assert(false);
	return nullptr;
}
