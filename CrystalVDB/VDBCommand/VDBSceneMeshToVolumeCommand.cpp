#include "VDBSceneMeshToVolumeCommand.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneMeshToVolume";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
	PublicLabel DivideLengthLabel = "DivideLength";
	PublicLabel NewSceneIdLabel = "NewSceneId";
}

//#include "CrystalScene/Scene/ParticleSystemScene.h"
//#include "CrystalScene/Scene/PolygonMeshScene.h"

#include "../CrystalVDB/VDBVolumeConverter.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "../CrystalVDB/VDBScene.h"

#include "../CrystalVDB/VDBMeshToVolumeConverter.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneMeshToVolumeCommand::Args::Args() :
	vdbSceneId(::VDBSceneIdLabel, -1),
	divideLength(::DivideLengthLabel, 1.0f)
{
	add(&vdbSceneId);
	add(&divideLength);
}

VDBSceneMeshToVolumeCommand::Results::Results() :
	newSceneId(::NewSceneIdLabel, -1)
{
	add(&newSceneId);
}

VDBSceneMeshToVolumeCommand::VDBSceneMeshToVolumeCommand() :
	ICommand(&args, &results)
{}

VDBSceneMeshToVolumeCommand::VDBSceneMeshToVolumeCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneMeshToVolumeCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneMeshToVolumeCommand::execute(World* world)
{
	auto vdbScene = world->getScenes()->findSceneById<VDBScene*>(args.vdbSceneId.getValue());
	if (vdbScene == nullptr) {
		return false;
	}

	const auto meshes = vdbScene->getMeshes();
	if (meshes.empty()) {
		return false;
	}

	auto newScene = new VDBScene(world->getNextSceneId(), "");
	for (auto mesh : meshes) {
		auto v = VDBMeshToVolumeConverter::toVolume(*mesh, args.divideLength.getValue());
		newScene->add(v);
	}
	world->getScenes()->addScene(newScene);
	results.newSceneId.setValue(newScene->getId());

	return true;
}
