#include "SceneSetCommand.h"

#include "PublicLabel.h"

namespace SceneSetLabels
{
	PublicLabel CommandNameLabel = "SceneSet";
	PublicLabel IdLabel = "Id";
	PublicLabel NameLabel = "Name";
}

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

SceneSetCommand::Args::Args() :
	id(SceneSetLabels::IdLabel, -1),
	name(SceneSetLabels::NameLabel, std::string(""))
{
	add(&id);
	add(&name);
}

SceneSetCommand::SceneSetCommand() :
	ICommand(&args, &results)
{
}

std::string SceneSetCommand::getName()
{
	return SceneSetLabels::CommandNameLabel;
}

bool SceneSetCommand::execute(World* world)
{
	const auto id = args.id.getValue();
	auto scene = world->getScenes()->findSceneById(id);
	if (scene == nullptr) {
		return false;
	}
	scene->setName(args.name.getValue());
	return true;
}
