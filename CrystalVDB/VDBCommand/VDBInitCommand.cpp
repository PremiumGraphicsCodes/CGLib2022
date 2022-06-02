#include "VDBInitCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBInit";
}

#include "../CrystalVDB/VDBAdapter.h"

using namespace Crystal::VDB;
using namespace Crystal::Scene;

VDBInitCommand::Args::Args()
{
}

VDBInitCommand::Results::Results()
{
}

VDBInitCommand::VDBInitCommand() :
	ICommand(&args, &results)
{
}

std::string VDBInitCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBInitCommand::execute(World* world)
{
	VDBAdapter::init();
	return true;
}

