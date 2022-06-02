#include "VDBSceneFileWriteCommand.h"

#include "../CrystalVDB/VDBFileWriter.h"
#include "../CrystalVDB/VDBVolumeScene.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalVDB/CrystalVDB/VDBScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneFileWrite";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
	PublicLabel FilePathLabel = "FilePath";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneFileWriteCommand::Args::Args() :
	vdbSceneId(::VDBSceneIdLabel, {}),
	filePath(::FilePathLabel, "")
{
	add(&vdbSceneId);
	add(&filePath);
}

VDBSceneFileWriteCommand::Results::Results()
{
}

VDBSceneFileWriteCommand::VDBSceneFileWriteCommand() :
	ICommand(&args, &results)
{}

VDBSceneFileWriteCommand::VDBSceneFileWriteCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneFileWriteCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneFileWriteCommand::execute(World* world)
{
	VDBFileWriter writer;
	const std::string str(args.filePath.getValue());
	const auto isOk = writer.open(str);
	if (!isOk) {
		return false;
	}
	auto scene = world->getScenes()->findSceneById<VDBScene*>(args.vdbSceneId.getValue());
	if (scene == nullptr) {
		return false;
	}
	const auto points = scene->getPoints();
	for (auto pts : points) {
		writer.writePoints(scene->getName(), pts);
	}
	const auto volumes = scene->getVolumes();
	if (!volumes.empty()) {
		writer.writeVolumes(volumes);
	}

	return true;
}