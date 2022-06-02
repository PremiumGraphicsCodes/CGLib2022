#include "VDBSceneCreateCommand.h"

#include "../../CrystalVDB/CrystalVDB/VDBPointsScene.h"
#include "../../CrystalVDB/CrystalVDB/VDBPolygonMeshScene.h"
#include "../../CrystalVDB/CrystalVDB/VDBVolumeScene.h"
#include "../../CrystalVDB/CrystalVDB/VDBScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneCreate";
	PublicLabel SceneTypeLabel = "SceneType";
	PublicLabel SceneType_VDBPointsLabel = "VDBPoints";
	PublicLabel SceneType_VDBMeshLabel = "VDBMesh";
	PublicLabel SceneType_VDBVolumeLabel = "VDBVolume";
	PublicLabel SceneType_VDBSceneLabel = "VDBScene";
	PublicLabel NameLabel = "Name";
	PublicLabel NewIdLabel = "NewId";
	PublicLabel PositionsLabel = "Positions";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::VDB;

VDBSceneCreateCommand::Args::Args() :
	sceneType(::SceneTypeLabel, ::SceneType_VDBPointsLabel),
	name(::NameLabel, ""),
	positions(::PositionsLabel, {})
{
	add(&sceneType);
	add(&name);
	add(&positions);
}

VDBSceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, -1)
{
	add(&newId);
}

std::string VDBSceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneCreateCommand::execute(World* world)
{
	const auto typeName = args.sceneType.getValue();
	const auto name = args.name.getValue();
	if (typeName == ::SceneType_VDBPointsLabel) {
		auto mesh = new VDBPointsScene(world->getNextSceneId(), name);
		world->addScene(mesh);
		results.newId.setValue(mesh->getId());
	}
	else if (typeName == ::SceneType_VDBMeshLabel) {
		auto mesh = new VDBMeshScene(world->getNextSceneId(), name);
		world->addScene(mesh);
		results.newId.setValue(mesh->getId());
	}
	else if (typeName == ::SceneType_VDBVolumeLabel) {
		auto mesh = new VDBVolumeScene(world->getNextSceneId(), name);
		world->addScene(mesh);
		results.newId.setValue(mesh->getId());
	}
	else if (typeName == ::SceneType_VDBSceneLabel) {
		auto scene = new VDBScene(world->getNextSceneId(), name);
		world->addScene(scene);
		results.newId.setValue(scene->getId());
	}
	else {
		assert(false);
		return false;
	}
	return true;
}
