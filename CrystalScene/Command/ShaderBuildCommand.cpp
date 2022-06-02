#include "ShaderBuildCommand.h"

#include "PublicLabel.h"

namespace ShaderBuildLabels
{
	PublicLabel CommandNameLabel = "ShaderBuild";
	PublicLabel IdLabel = "Id";
}

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

ShaderBuildCommand::Args::Args() :
	id(ShaderBuildLabels::IdLabel, 0)
{
	add(&id);
}

std::string ShaderBuildCommand::getName()
{
	return ShaderBuildLabels::CommandNameLabel;
}

bool ShaderBuildCommand::execute(World* world)
{
	auto s = world->getScenes()->findSceneById(std::any_cast<int>(args.id.getValue()));
	s->getPresenter()->createView(world->getRenderer());
	return true;
}

