#include "STLFileExportCommand.h"

#include "../../Crystal/IO/STLFileWriter.h"

#include "../Scene/PolygonMeshScene.h"
#include "../Scene/TriangleMeshScene.h"

#include "PublicLabel.h"

namespace STLFileExportLabels
{
	PublicLabel CommandNameLabel = "STLFileExport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IdsLabel = "Ids";
	PublicLabel IsBinaryLabel = "IsBinary";
}

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

STLFileExportCommand::Args::Args() :
	ids(STLFileExportLabels::IdsLabel, {}),
	isBinary(STLFileExportLabels::IsBinaryLabel, false),
	filePath(STLFileExportLabels::FilePathLabel, "")
{
	add(&ids);
	add(&isBinary);
	add(&filePath);
}

STLFileExportCommand::Results::Results()// :
//	isOk(FileExportLabels::IsOkLabel, false)
{
//	add(&isOk);
}

std::string STLFileExportCommand::getName()
{
	return STLFileExportLabels::CommandNameLabel;
}

bool STLFileExportCommand::execute(World* world)
{
	const auto ids = args.ids.getValue();

	STLFile stl;
	std::vector<STLFace> fs;
	for (const auto id : ids) {
		auto triangleMesh = world->getScenes()->findSceneById<TriangleMeshScene*>(id);
		const auto faces = triangleMesh->getShape()->getFaces();
		for (const auto f : faces) {
			STLFace sf(f.triangle, f.normal);
			fs.push_back(sf);
		}
	}
	stl.faces = fs;
	stl.faceCount = fs.size();

	if (args.isBinary.getValue()) {
		STLFileWriter writer;
		return writer.writeBinary(args.filePath.getValue(), stl);
	}
	else {
		STLFileWriter writer;
		return writer.writeAscii(args.filePath.getValue(), stl);
	}
	return false;
}