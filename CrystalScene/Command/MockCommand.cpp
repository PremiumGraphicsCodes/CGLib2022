#include "MockCommand.h"

#include "PublicLabel.h"

namespace MockLabels
{
	PublicLabel MockCommandLabel = "Mock";
}

using namespace Crystal::Command;

std::string MockCommand::getName()
{
	return MockLabels::MockCommandLabel;
}

bool MockCommand::execute(Crystal::Scene::World* world)
{
	results.value.setValue( args.lhs.getValue() + args.rhs.getValue() );
	return true;
}