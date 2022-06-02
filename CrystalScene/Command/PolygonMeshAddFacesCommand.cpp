#include "PolygonMeshAddFacesCommand.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../Scene/PolygonMeshScene.h"

#include "PublicLabel.h"

namespace PolygonMeshAddFacesLabels
{
	PublicLabel CommandNameLabel = "PolygonMeshAddFaces";
	PublicLabel PolygonMeshIdLabel = "PolygonMeshId";

	PublicLabel VertexIdsLabel = "VertexIds";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshAddFacesCommand::Args::Args() :
	meshId(PolygonMeshAddFacesLabels::PolygonMeshIdLabel, -1),
	vertexIds(PolygonMeshAddFacesLabels::VertexIdsLabel, {})
{
	add(&meshId);
	add(&vertexIds);
}

PolygonMeshAddFacesCommand::Results::Results()
{
}

std::string PolygonMeshAddFacesCommand::getName()
{
	return ::PolygonMeshAddFacesLabels::CommandNameLabel;
}

bool PolygonMeshAddFacesCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<PolygonMeshScene*>(args.meshId.getValue());
	auto shape = scene->getShape();
	const auto vertexIds = args.vertexIds.getValue();

	const auto faceId = static_cast<int>( shape->getFaces().size() );
	Face f(vertexIds[0], vertexIds[1], vertexIds[2], faceId);
	shape->faces.push_back(f);

	/*
	for (int i = 0; i < positionIds.size(); ++i) {
		Vertex v;
		v.positionId = positionIds[i];
		v.normalId = normalIds[i];
		v.texCoordId = texCoordIds[i];
		shape->vertices.push_back(v);
	}
	*/

	return true;
}
