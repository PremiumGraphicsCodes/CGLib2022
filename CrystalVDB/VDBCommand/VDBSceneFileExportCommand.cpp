#include "VDBSceneFileExportCommand.h"


#include "../CrystalVDB/VDBPointsScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

#include "CrystalVDB/CrystalVDB/VDBFileExporter.h"

#include "CrystalVDB/CrystalVDB/VDBScene.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneFileExport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel FileFormatLabel = "FileFormat";
	PublicLabel FileFormat_PLY_Label = "PLY";
	PublicLabel FileFormat_PCD_Label = "PCD";
	PublicLabel FileFormat_OBJ_Label = "OBJ";
	PublicLabel FileFormat_STL_Label = "STL";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

namespace {
	VDBFileExporter::Format toFormat(const std::string& format) {
		if (format == FileFormat_PLY_Label) {
			return VDBFileExporter::Format::PLY;
		}
		else if (format == FileFormat_PCD_Label) {
			return VDBFileExporter::Format::PCD;
		}
		else if (format == FileFormat_STL_Label) {
			return VDBFileExporter::Format::STL;
		}
		else if (format == FileFormat_OBJ_Label) {
			assert(false);
			return VDBFileExporter::Format::OBJ;
		}
		assert(false);
		return VDBFileExporter::Format::OBJ;
	}
}


VDBSceneFileExportCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	fileFormat(::FileFormatLabel, ""),
	vdbSceneId(::VDBSceneIdLabel, -1)
{
	add(&filePath);
	add(&fileFormat);
	add(&vdbSceneId);
}

VDBSceneFileExportCommand::Results::Results()
{
}

VDBSceneFileExportCommand::VDBSceneFileExportCommand() :
	ICommand(&args, &results)
{}

VDBSceneFileExportCommand::VDBSceneFileExportCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneFileExportCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneFileExportCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBScene*>(args.vdbSceneId.getValue());
	if (scene == nullptr) {
		return false;
	}

	VDBFileExporter exporter(scene);

	const auto filePath = args.filePath.getValue();
	const auto format = ::toFormat( args.fileFormat.getValue() );

	const auto isOk = exporter.write(filePath, format);
	return isOk;
}

