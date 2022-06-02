#include "PolygonMeshAddVerticesCommand.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../Scene/PolygonMeshScene.h"

#include "PublicLabel.h"

namespace PolygonMeshAddVerticesLabels
{
	PublicLabel CommandNameLabel = "PolygonMeshAddVertices";
	PublicLabel PolygonMeshIdLabel = "PolygonMeshId";

	PublicLabel PositionIdsLabel = "PositionIds";
	PublicLabel NormalIdsLabel = "NormalIds";
	PublicLabel TexCoordIdsLabel = "TexCoordIds";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshAddVerticesCommand::Args::Args() :
	meshId(PolygonMeshAddVerticesLabels::PolygonMeshIdLabel, -1),
	positionsIds(PolygonMeshAddVerticesLabels::PositionIdsLabel, {}),
	normalIds(PolygonMeshAddVerticesLabels::NormalIdsLabel, {}),
	texCoordIds(PolygonMeshAddVerticesLabels::TexCoordIdsLabel, {})
{
	add(&meshId);
	add(&positionsIds);
	add(&normalIds);
	add(&texCoordIds);
}

PolygonMeshAddVerticesCommand::Results::Results()
{
}

std::string PolygonMeshAddVerticesCommand::getName()
{
	return ::PolygonMeshAddVerticesLabels::CommandNameLabel;
}

bool PolygonMeshAddVerticesCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<PolygonMeshScene*>(args.meshId.getValue());
	auto shape = scene->getShape();
	const auto positionIds = args.positionsIds.getValue();
	const auto normalIds = args.normalIds.getValue();
	const auto texCoordIds = args.texCoordIds.getValue();

	for(int i = 0; i < positionIds.size(); ++i) {
		Vertex v;
		v.positionId = positionIds[i];
		v.normalId = normalIds[i];
		v.texCoordId = texCoordIds[i];
		shape->vertices.push_back(v);
	}

	return true;
}
