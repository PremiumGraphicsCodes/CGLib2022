#include "DeleteCommand.h"

#include "PublicLabel.h"

namespace DeleteLabels
{
	PublicLabel CommandNameLabel = "DeleteCommand";
	PublicLabel IdLabel = "Id";
}

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string DeleteCommand::getName()
{
	return DeleteLabels::CommandNameLabel;
}

DeleteCommand::Args::Args() :
	id(DeleteLabels::IdLabel, -1)
{
	add(&id);
}

DeleteCommand::DeleteCommand() :
	ICommand(&args, nullptr)
{}

bool DeleteCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById(args.id.getValue());
	if (scene == nullptr) {
		return false;
	}
	world->getScenes()->deleteSceneById(args.id.getValue());
	return true;
}
