#include "CSGBoundarySceneUpdateCommand.h"

#include "CrystalScene/Scene/SolidScene.h"

#include "../CrystalPhysics/Boundary/CSGBoundaryScene.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "CSGBoundarySceneUpdate";
	PublicLabel IdLabel = "Id";
	PublicLabel BoundingBoxLabel = "BoundingBox";
	PublicLabel NameLabel = "Name";
}

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string CSGBoundarySceneUpdateCommand::getName()
{
	return ::CommandNameLabel;
}

CSGBoundarySceneUpdateCommand::Args::Args() :
	id(::IdLabel, -1),
	bb(::BoundingBoxLabel, Math::Box3dd()),
	name(::NameLabel, std::string("CSGBoundary"))
{
	add(&id);
	add(&bb);
	add(&name);
}

CSGBoundarySceneUpdateCommand::Results::Results()
{
}

CSGBoundarySceneUpdateCommand::CSGBoundarySceneUpdateCommand() :
	ICommand(&args, &results)
{}

bool CSGBoundarySceneUpdateCommand::execute(World* world)
{
	auto boundaryScene = world->getScenes()->findSceneById<CSGBoundaryScene*>(args.id.getValue());

	boundaryScene->clearBoxes();
	boundaryScene->setName(args.name.getValue());
	boundaryScene->add(args.bb.getValue());
	world->getScenes()->addScene(boundaryScene);

	//results.newId.setValue(boundaryScene->getId());

	return true;
}