#include "ClearCommand.h"

#include "PublicLabel.h"

namespace ClearLabels
{
	PublicLabel CommandNameLabel = "ClearCommand";
}

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string ClearCommand::getName()
{
	return ClearLabels::CommandNameLabel;
}

ClearCommand::Args::Args()
{
}

ClearCommand::ClearCommand() :
	ICommand(&args, nullptr)
{}

bool ClearCommand::execute(World* world)
{
	world->clear();
	return true;
}
