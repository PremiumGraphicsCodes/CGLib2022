#include "FileExportCommand.h"

#include "Command.h"
#include "CommandFactory.h"

#include "PublicLabel.h"

#include "OBJFileExportCommand.h"
#include "STLFileExportCommand.h"
#include "PCDFileExportCommand.h"

namespace FileExportLabels
{
	PublicLabel FileExportCommandLabel = "FileExport";
	PublicLabel FilePathLabel = "FilePath";
}

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

FileExportCommand::Args::Args() :
	filePath(FileExportLabels::FilePathLabel, "")
{
	add(&filePath);
}

FileExportCommand::Results::Results()
{
	//add(&isOk);
}

std::string FileExportCommand::getName()
{
	return FileExportLabels::FileExportCommandLabel;
}

bool FileExportCommand::execute(World* world)
{
	const auto filePath(args.filePath.getValue());
	const auto format = Crystal::IO::getFileFormat(filePath);
	return exportFile(filePath, format, world);
}

bool FileExportCommand::exportFile(const std::filesystem::path& filePath, const FileFormat format, World* world)
{
	//switch (format) {
	//case FileFormat::OBJ :
	//{
	//	std::vector<int> ids;
	//	auto scenes = world->getScenes()->findScenes(SceneTypeLabels::PolygonMeshScene);
	//	for (auto s : scenes) {
	//		ids.push_back(s->getId());
	//	}

	//	auto command = OBJFileExportCommand();
	//	command.setArg(::OBJFileExportLabels::FilePathLabel, args.filePath.getValue());
	//	command.setArg(::OBJFileExportLabels::IdsLabel, ids);
	//	return command->execute(world);
	//}
	///*
	//case FileFormat::MTL :
	//{
	//	OBJFileExporter exporter;
	//	return exporter.exportMTL(filePath, objects);
	//}
	//*/
	//case FileFormat::STL_ASCII :
	//{
	//	/*
	//	std::vector<int> ids;
	//	auto scenes = world->getScenes()->findScenes(SceneType::TriangleMeshScene);
	//	for (auto s : scenes) {
	//		ids.push_back(s->getId());
	//	}
	//	*/

	//	auto command = CommandFactory::create(::OBJFileExportLabels::CommandNameLabel);
	//	command->setArg(::STLFileExportLabels::FilePathLabel, args.filePath.getValue());
	//	command->setArg(::STLFileExportLabels::IsBinaryLabel, false);
	//	return command->execute(world);
	//}
	//case FileFormat::STL_BINARY :
	//{
	//	auto command = CommandFactory::create(::STLFileExportLabels::CommandNameLabel);
	//	command->setArg(::STLFileExportLabels::FilePathLabel, args.filePath.getValue());
	//	command->setArg(::STLFileExportLabels::IsBinaryLabel, true);
	//	return command->execute(world);
	//}
	//case FileFormat::PCD :
	//{
	//	auto command = CommandFactory::create(::PCDFileExportLabels::CommandNameLabel);
	//	std::vector<int> ids;
	//	auto scenes = world->getScenes()->findScenes(SceneTypeLabels::ParticleSystemScene);
	//	for (auto s : scenes) {
	//		ids.push_back(s->getId());
	//	}
	//	command->setArg(::PCDFileExportLabels::IdsLabel, ids);
	//	command->setArg(::PCDFileExportLabels::FilePathLabel, args.filePath.getValue());
	//	return command->execute(world);
	//}
	//default :
	//	assert(false);
	//	return false;
	//}
	return false;
}

