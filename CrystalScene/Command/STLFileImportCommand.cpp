#include "STLFileImportCommand.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../Scene/TriangleMeshScene.h"

#include "../../Crystal/IO/STLFileReader.h"

#include "PublicLabel.h"

namespace STLFileImportLabels
{
	PublicLabel CommandNameLabel = "STLFileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel TriangleMeshIdLabel = "TriangleMeshId";
}

using namespace Crystal::IO;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

STLFileImportCommand::Args::Args() :
	filePath(STLFileImportLabels::FilePathLabel, ""),
	id(STLFileImportLabels::TriangleMeshIdLabel, -1)
{
	add(&filePath);
	add(&id);
}

STLFileImportCommand::Results::Results()
{
}

std::string STLFileImportCommand::getName()
{
	return STLFileImportLabels::CommandNameLabel;
}

bool STLFileImportCommand::execute(Crystal::Scene::World* scene)
{
	const auto meshScene = scene->getScenes()->findSceneById<TriangleMeshScene*>(args.id.getValue());
	if (meshScene == nullptr) {
		return false;
	}

	const auto isBinary = STLFileReader::isBinary(args.filePath.getValue());
	if (!isBinary) {
		STLFileReader reader;
		const auto isOk = reader.readAscii(args.filePath.getValue());
		/*
		if (!isOk) {
			return false;
		}
		*/
		PolygonMeshBuilder builder;
		const auto& stl = reader.getSTL();
		auto mesh = std::make_unique<TriangleMesh>();
		const auto faces = stl.faces;
		for (const auto& f : faces) {
			TriangleFace tf(f.triangle, f.normal);
			mesh->addFace(tf);
		}
		meshScene->setShape(std::move(mesh));
		return true;
	}
	else {
		STLFileReader reader;
		if (reader.readBinary(args.filePath.getValue())) {
			PolygonMeshBuilder builder;
			const auto& stl = reader.getSTL();
			auto mesh = std::make_unique<TriangleMesh>();
			const auto faces = stl.faces;
			for (const auto& f : faces) {
				TriangleFace tf(f.triangle, f.normal);
				mesh->addFace(tf);
			}
			meshScene->setShape(std::move(mesh));
			return true;
		}
	}
	return false;
}