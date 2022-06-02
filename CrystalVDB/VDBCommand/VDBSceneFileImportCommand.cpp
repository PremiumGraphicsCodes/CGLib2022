#include "VDBSceneFileImportCommand.h"

#include "../CrystalVDB/VDBScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

#include "CrystalVDB/CrystalVDB/VDBFileImporter.h"

#include <iostream>

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneFileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel FileFormatLabel = "FileFormat";
	PublicLabel FileFormat_PLY_Label = "PLY";
	PublicLabel FileFormat_PCD_Label = "PCD";
	PublicLabel FileFormat_OBJ_Label = "OBJ";
	PublicLabel FileFormat_STL_Label = "STL";
	PublicLabel NewSceneIdLabel = "NewSceneId";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

namespace {
	VDBFileImporter::Format toFormat(const std::string& format) {
		if (format == FileFormat_PLY_Label) {
			return VDBFileImporter::Format::PLY;
		}
		else if (format == FileFormat_PCD_Label) {
			return VDBFileImporter::Format::PCD;
		}
		else if (format == FileFormat_STL_Label) {
			return VDBFileImporter::Format::STL;
		}
		else if (format == FileFormat_OBJ_Label) {
			return VDBFileImporter::Format::OBJ;
		}
		assert(false);
		return VDBFileImporter::Format::NONE;
	}
}

VDBSceneFileImportCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	fileFormat(::FileFormatLabel, "")
{
	add(&filePath);
	add(&fileFormat);
}

VDBSceneFileImportCommand::Results::Results() :
	newSceneId(::NewSceneIdLabel, -1)
{
	add(&newSceneId);
}

VDBSceneFileImportCommand::VDBSceneFileImportCommand() :
	ICommand(&args, &results)
{}

VDBSceneFileImportCommand::VDBSceneFileImportCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneFileImportCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneFileImportCommand::execute(World* world)
{
	const auto format = args.fileFormat.getValue();
	const auto filePath = args.filePath.getValue();

	const auto f = ::toFormat(format);
	VDBFileImporter importer;
	auto scene = importer.read(filePath, f);
	if (scene == nullptr) {
		return false;
	}
	scene->setId(world->getNextSceneId());
	scene->setName("Imported");
	world->addScene(scene);
	results.newSceneId.setValue(scene->getId());
	return true;
}

