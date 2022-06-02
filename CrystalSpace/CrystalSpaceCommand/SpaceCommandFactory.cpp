#include "SpaceCommandFactory.h"

#include "SparseVolumeSceneCreateCommand.h"
#include "SparseVolumeNodeSetCommand.h"
#include "VoxelSceneCreateCommand.h"
#include "VoxelSetCommand.h"
#include "VoxelGetCommand.h"
#include "MeshToPSCommand.h"
#include "MeshToVoxelCommand.h"
#include "VoxelToPSCommand.h"
#include "VoxelizerCommand.h"

using namespace Crystal::Command;
using namespace Crystal::Space;

std::unique_ptr<ICommand> SpaceCommandFactory::create(const std::string& name)
{
	if (name == SparseVolumeSceneCreateCommand::getName()) {
		return std::make_unique<SparseVolumeSceneCreateCommand>();
	}
	else if (name == SparseVolumeNodeSetCommand::getName()) {
		return std::make_unique<SparseVolumeNodeSetCommand>();
	}
	else if (name == VoxelSceneCreateCommand::getName()) {
		return std::make_unique<VoxelSceneCreateCommand>();
	}
	else if (name == VoxelSetCommand::getName()) {
		return std::make_unique<VoxelSetCommand>();
	}
	else if (name == VoxelGetCommand::getName()) {
		return std::make_unique<VoxelGetCommand>();
	}
	else if (name == MeshToPSCommand::getName()) {
		return std::make_unique<MeshToPSCommand>();
	}
	else if (name == MeshToVoxelCommand::getName()) {
		return std::make_unique<MeshToVoxelCommand>();
	}
	else if (name == VoxelToPSCommand::getName()) {
		return std::make_unique<VoxelToPSCommand>();
	}
	else if (name == VoxelizerCommand::getName()) {
		return std::make_unique<VoxelizerCommand>();
	}
	assert(false);
	return nullptr;
}
