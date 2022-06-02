#include "OBJFileImportCommand.h"

#include "PublicLabel.h"

namespace OBJFileImportLabels
{
	PublicLabel CommandNameLabel = "OBJFileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel NewIdLabel = "NewId";
}

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../../Crystal/IO/OBJFileReader.h"
#include "../../Crystal/IO/MTLFileReader.h"

#include "../Scene/Scene.h"
#include "../Scene/PolygonMeshScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

OBJFileImportCommand::Args::Args() :
	filePath(OBJFileImportLabels::FilePathLabel, std::string(""))
{
	add(&filePath);
}

OBJFileImportCommand::Results::Results() :
	newId(OBJFileImportLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string OBJFileImportCommand::getName()
{
	return OBJFileImportLabels::CommandNameLabel;
}

bool OBJFileImportCommand::execute(World* scene)
{
	const std::string filePath(args.filePath.getValue());
	const auto isOk = importOBJ(filePath, scene);
	return isOk;
}

bool OBJFileImportCommand::importOBJ(const std::filesystem::path& filePath, World* world)
{
	OBJFileReader reader;
	if (reader.read(filePath)) {
		const auto& obj = reader.getOBJ();
		const auto& positions = obj.positions;
		const auto& normals = obj.normals;
		const auto& texCoords = obj.texCoords;

		PolygonMeshBuilder builder;
		for (const auto& p : positions) {
			builder.createPosition(p);
		}
		for (const auto& n : normals) {
			builder.createNormal(n);
		}
		for (const auto& tc : texCoords) {
			builder.createTexCoord(tc);
		}


		std::vector< std::vector<int> > indices;
		for (const auto& g : obj.groups) {
			//auto faceGroup = world->getSceneFactory()->createFaceGroupScene(meshScene, g.name);
			//auto groupScene = new FaceGroupScene(world->getNextSceneId(), g.name, meshScene);
			//meshScene->addGroup(groupScene);

			for (const auto& f : g.faces) {
				std::vector<int> indices;
				for (int i = 0; i < f.positionIndices.size(); i++) {
					const auto p = f.positionIndices[i] - 1;
					const auto n = f.normalIndices[i] - 1;
					const auto tc = f.texCoordIndices[i] - 1;
					const auto v = builder.createVertex(p, n, tc);
					indices.push_back(v);
				}
				/*
				if (indices.size() == 3) {
					builder.createFace(indices[0], indices[1], indices[2]);
				}
				*/

				//indices.push_back(eachIndices);
				int origin = indices[0];
				int i1 = 1;
				int i2 = 2;
				for (int i = 0; i2 < indices.size(); i++) {
					builder.createFace(origin, indices[i1], indices[i2]);
					i1++;
					i2++;
				}
//				faceGroup->addFace(f);
			}
			//faceGroup->setMaterialName(g.usemtl);
		}

		auto polygonMesh = builder.build();
		auto meshScene = new PolygonMeshScene(world->getNextSceneId(), "PolygonMesh", std::move(polygonMesh));//world->getSceneFactory()->createPolygonMeshScene(std::move(polygonMesh), "PolygonMesh");
//		meshScene->addGroup()

		world->getScenes()->addScene(meshScene);
		results.newId.setValue(meshScene->getId());

		return true;
	}
	return false;
}

bool OBJFileImportCommand::importMTL(const std::filesystem::path& filePath, World* world)
{
	MTLFileReader reader;
	if (reader.read(filePath)) {
		const auto& mtl = reader.getMTL();
		for (const auto& m : mtl.materials) {
			auto mat = std::make_unique<Material>();
			mat->ambient = m.ambient;
			mat->diffuse = m.diffuse;
			mat->specular = m.specular;
			mat->shininess = m.specularExponent;
			world->getScenes()->addScene(new MaterialScene(world->getNextSceneId(), m.name, std::move(mat)));
			//mat.textureId = m.ambientTexture;
		}
		return true;
	}
	return false;
}

bool OBJFileImportCommand::importOBJWithMTL(const std::filesystem::path& filePath, World* world)
{
	// path から .objファイル名を取得する．
	auto filename = filePath.parent_path() / filePath.stem();
	filename.concat(".mtl");

	auto scene = new Crystal::Scene::Scene(world->getNextSceneId(), "OBJ");//world->getSceneFactory()->createScene("OBJ");

	// mtl ファイルを読み込む．
	if (!importMTL(filename, world)) {
		return false;
	}

	// obj ファイルを読み込む．
	if (!importOBJ(filePath, world)) {
		return false;
	}

	world->getScenes()->addScene(scene);

	return true;
}