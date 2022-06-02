#include "FileImportCommand.h"

#include "../../Crystal/IO/FileFormat.h"

#include "PublicLabel.h"

namespace FileImportLabels
{
	PublicLabel FileImportCommandLabel = "FileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IsOkLabel = "IsOk";
	PublicLabel NewIdLabel = "NewId";

	PublicLabel STLFileImportCommandLabel = "STLFileImport";
}
#include "Command.h"
#include "CommandFactory.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

FileImportCommand::Args::Args() :
	filePath(FileImportLabels::FilePathLabel, std::string(""))
{
	add(&filePath);
}

FileImportCommand::Results::Results() :
	newId(FileImportLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string FileImportCommand::getName()
{
	return FileImportLabels::FileImportCommandLabel;
}

bool FileImportCommand::execute(World* scene)
{
	if (!importFile(args.filePath.getValue(), scene)) {
		return false;
	}
	return true;
	//scene->getObjects()
}

bool FileImportCommand::importFile(const std::filesystem::path& filePath, World* world)
{
	const auto format = getFileFormat(filePath);
	return importFile(filePath, world, format);
}

bool FileImportCommand::importFile(const std::filesystem::path& filePath, World* world, const FileFormat format)
{
//	switch (format) {
//	case FileFormat::OBJ:
//	{
//		auto command = CommandFactory::create(::OBJFileImportLabels::CommandNameLabel);
//		command->setArg(::OBJFileImportLabels::FilePathLabel, args.filePath.getValue());
//		const auto isOk = command->execute(world);
//		const auto newId = command->getResult(::OBJFileImportLabels::NewIdLabel);
//		results.newId.setValue( std::any_cast<int>( newId ) );
//		//OBJFileImporter importer(factory);
//		//return importer.importOBJWithMTL(filePath, parent);
//		return isOk;
//	}
//	case FileFormat::MTL:
//	{
////		OBJFileImporter importer(factory);
////		return importer.importMTL(filePath, parent);
//		return false;
//	}
//	case FileFormat::STL:
//	{
//		auto command = CommandFactory::create(STLFileImportLabels::CommandNameLabel);
//		command->setArg(STLFileImportLabels::FilePathLabel, this->args.filePath.getValue());
//		const auto isOk = command->execute(world);
//		return isOk;
//	}
//	case FileFormat::PCD:
//	{
//		auto command = CommandFactory::create(::PCDFileImportLabels::CommandNameLabel);
//		command->setArg(::PCDFileImportLabels::FilePathLabel, this->args.filePath.getValue());
//		const auto isOk = command->execute(world);
//		return isOk;
//	}
//	default:
//		assert(false);
//	}
	return false;
}