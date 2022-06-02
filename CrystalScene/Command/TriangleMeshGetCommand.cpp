#include "TriangleMeshGetCommand.h"

#include "../Scene/TriangleMeshScene.h"

#include "PublicLabel.h"

namespace TriangleMeshGetLabels
{
	PublicLabel CommandNameLabel = "TriangleMeshGet";
	PublicLabel MeshIdLabel = "MeshId";
	PublicLabel LayerLabel = "Layer";
	PublicLabel TrianglesLabel = "Triangles";
	PublicLabel NormalsLabel = "Normals";
	PublicLabel NameLabel = "Name";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TriangleMeshGetCommand::Args::Args() :
	meshId(TriangleMeshGetLabels::MeshIdLabel, -1),
	layer(TriangleMeshGetLabels::LayerLabel, 1)
{
	add(&meshId);
	add(&layer);
}

TriangleMeshGetCommand::Results::Results() :
	triangles(TriangleMeshGetLabels::TrianglesLabel, {}),
	normals(TriangleMeshGetLabels::NormalsLabel, {}),
	name(TriangleMeshGetLabels::NameLabel, std::string(""))
{
	add(&triangles);
	add(&normals);
	add(&name);
}

std::string TriangleMeshGetCommand::getName()
{
	return TriangleMeshGetLabels::CommandNameLabel;
}

bool TriangleMeshGetCommand::execute(World* world)
{
	const auto scene = world->getScenes()->findSceneById<TriangleMeshScene*>(args.meshId.getValue());
	if (scene == nullptr) {
		return false;
	}

	const auto faces = scene->getShape()->getFaces();
	std::vector<Triangle3d> triangles;
	std::vector<Vector3dd> normals;

	for (const auto& f : faces) {
		triangles.push_back(f.triangle);
		normals.push_back(f.normal);
	}

	results.triangles.setValue(triangles);
	results.normals.setValue(normals);
	results.name.setValue(scene->getName());
	return true;
}
