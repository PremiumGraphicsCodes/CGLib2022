#include "MeshBoundarySceneCreateCommand.h"

#include "../CrystalPhysics/Boundary/MeshBoundaryScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "MeshBoundarySceneCreate";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string MeshBoundarySceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

MeshBoundarySceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, 0)
{
	add(&newId);
}

MeshBoundarySceneCreateCommand::MeshBoundarySceneCreateCommand() :
	ICommand(&args, &results)
{}

bool MeshBoundarySceneCreateCommand::execute(World* world)
{
	auto boundaryScene = new MeshBoundaryScene(world->getNextSceneId(), "");
	world->getScenes()->addScene(boundaryScene);

	results.newId.setValue(boundaryScene->getId());

	return true;
}