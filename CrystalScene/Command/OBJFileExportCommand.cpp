#include "OBJFileExportCommand.h"

#include "../../Crystal/IO/OBJFileWriter.h"
#include "../../Crystal/IO/MTLFileWriter.h"

#include "../Scene/PolygonMeshScene.h"

#include "PublicLabel.h"

namespace OBJFileExportLabels
{
	PublicLabel CommandNameLabel = "OBJFileExport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IdsLabel = "Ids";
}

using namespace Crystal::Scene;
using namespace Crystal::IO;
using namespace Crystal::Command;

OBJFileExportCommand::Args::Args() :
	ids(OBJFileExportLabels::IdsLabel, {}),
	filePath(OBJFileExportLabels::FilePathLabel, "")
{
	add(&ids);
	add(&filePath);
}

OBJFileExportCommand::Results::Results()
{
}

std::string OBJFileExportCommand::getName()
{
	return OBJFileExportLabels::CommandNameLabel;
}

bool OBJFileExportCommand::execute(World* world)
{
	const auto& scenes = world->getScenes()->findScenes(SceneTypeLabels::PolygonMeshScene);
	std::vector<PolygonMeshScene*> polygons;
	for (const auto& scene : scenes) {
		polygons.push_back( static_cast<PolygonMeshScene*>( scene) );
	}
	const auto isOk = exportOBJ(args.filePath.getValue(), polygons);
	return isOk;
}

bool OBJFileExportCommand::exportOBJ(const std::filesystem::path& filePath, const std::vector<PolygonMeshScene*>& polygons)
{
	OBJFile obj;

	for (auto polygon : polygons) {
		obj.groups.push_back(OBJGroup());
		const auto& vertices = polygon->getShape()->getVertices();
		const auto& faces = polygon->getShape()->getFaces();

		const auto& positions = polygon->getShape()->getPositions();
		for (const auto& v : positions) {
			obj.positions.push_back(v);
		}
		const auto& normals = polygon->getShape()->getNormals();
		for (const auto& n : normals) {
			obj.normals.push_back(n);
		}
		const auto& tcs = polygon->getShape()->getTexCoords();
		for (const auto& tc : tcs) {
			obj.texCoords.push_back(tc);
		}

		for (auto f : faces) {
			std::vector<int> indices;
			const auto& vIds = f.getVertexIds();
			OBJFace face;
			for (const int vid : vIds) {
				face.positionIndices.push_back( vertices[vid].positionId +1 );
				face.normalIndices.push_back(vertices[vid].normalId +1);
				face.texCoordIndices.push_back(vertices[vid].texCoordId +1);
			}
			obj.groups[0].faces.push_back(face);
		}
	}

	OBJFileWriter writer;
	return writer.write(filePath, obj);
}

bool OBJFileExportCommand::exportMTL(const std::filesystem::path& filePath, PolygonMeshScene& appearances)
{
	/*
	MTLFileWriter writer;
	MTLFile mtl;
	for (const auto mat : objects.getMaterials()->getMaterials()) {
		MTL m;
		m.name = mat->getName();
		m.ambient = mat->getMaterial()->ambient;
		m.specular = mat->getMaterial()->specular;
		m.diffuse = mat->getMaterial()->diffuse;
		m.specularExponent = mat->getMaterial()->shininess;
		mtl.materials.push_back(m);
	}
	return writer.write(filePath, mtl);
	*/
	return false;
}
