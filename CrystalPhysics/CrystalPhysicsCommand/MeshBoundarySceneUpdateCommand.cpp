#include "MeshBoundarySceneUpdateCommand.h"

#include "CrystalScene/Scene/PolygonMeshScene.h"

#include "../CrystalPhysics/Boundary/MeshBoundaryScene.h"
//#include "../../Crystal/Scene/ParticleSystemScene.h"


#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "MeshBoundarySceneUpdate";
	PublicLabel IdLabel = "Id";
	PublicLabel MeshIdLabel = "MeshId";
	PublicLabel NameLabel = "Name";
}


using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string MeshBoundarySceneUpdateCommand::getName()
{
	return ::CommandNameLabel;
}

MeshBoundarySceneUpdateCommand::Args::Args() :
	id(::IdLabel, -1),
	meshId(::MeshIdLabel, -1),
	name(::NameLabel, std::string("MeshBoundary"))
{
	add(&id);
	add(&meshId);
	add(&name);
}

MeshBoundarySceneUpdateCommand::Results::Results()
{
}

MeshBoundarySceneUpdateCommand::MeshBoundarySceneUpdateCommand() :
	ICommand(&args, &results)
{}

bool MeshBoundarySceneUpdateCommand::execute(World* world)
{
	auto boundaryScene = world->getScenes()->findSceneById<MeshBoundaryScene*>(args.id.getValue());
	if (boundaryScene == nullptr) {
		return false;
	}

	auto meshId = args.meshId.getValue();
	if (meshId > 0) {
		auto meshScene = world->getScenes()->findSceneById<PolygonMeshScene*>(meshId);
		if (meshScene == nullptr) {
			return false;
		}
		boundaryScene->build(meshScene->getShape(), 1.0);
	}

	boundaryScene->clear();
	boundaryScene->setName(args.name.getValue());
	//boundaryScene->add(solidScene->getBoundingBox());
	world->getScenes()->addScene(boundaryScene);

	//results.newId.setValue(boundaryScene->getId());

	return true;
}