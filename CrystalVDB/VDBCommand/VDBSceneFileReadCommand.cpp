#include "VDBSceneFileReadCommand.h"

#include "../CrystalVDB/VDBFileReader.h"

#include "../CrystalVDB/VDBPointsScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneFileRead";
	PublicLabel RadiusLabel = "Radius";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneFileReadCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	radius(::RadiusLabel, 0.5f)
{
	add(&filePath);
	add(&radius);
}

VDBSceneFileReadCommand::Results::Results() :
	newId(::NewIdLabel, -1)
{
	add(&newId);
}

VDBSceneFileReadCommand::VDBSceneFileReadCommand() :
	ICommand(&args, &results)
{}

VDBSceneFileReadCommand::VDBSceneFileReadCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{
}

std::string VDBSceneFileReadCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneFileReadCommand::execute(World* world)
{
	VDBFileReader reader;
	const auto isOk = reader.open(args.filePath.getValue());
	if (!isOk) {
		return false;
	}
	reader.readMetaData();

	auto scene = new VDBScene(world->getNextSceneId(), "");

	const auto& pointNames = reader.getPointNames();
	std::vector<int> newIds;
	for (const auto& n : pointNames) {
		const auto pts = reader.readPositions(n, args.radius.getValue());
		pts->setName(n);
		scene->add(pts);
	}

	const auto& volumeNames = reader.getGridNames();
	for (const auto& n : volumeNames) {
		const auto vol = reader.readVolume(n);
		vol->setName(n);
		scene->add(vol);
	}

	world->addScene(scene);

	results.newId.setValue(scene->getId());
	//reader.get
	return true;
}