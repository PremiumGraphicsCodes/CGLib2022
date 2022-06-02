#include "CameraCreateCommand.h"

#include "PublicLabel.h"

namespace CameraCreateLabels
{
	PublicLabel CommandNameLabel = "CameraCreate";

	PublicLabel NewIdLabel = "NewId";
}

#include "../Scene/CameraScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string CameraCreateCommand::getName()
{
	return CameraCreateLabels::CommandNameLabel;
}

CameraCreateCommand::Args::Args()
{
}

CameraCreateCommand::Results::Results() :
	newId(CameraCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

bool CameraCreateCommand::execute(World* world)
{
	auto id = world->createDefaultCamera();
	results.newId.setValue(id);
	return true;
}
