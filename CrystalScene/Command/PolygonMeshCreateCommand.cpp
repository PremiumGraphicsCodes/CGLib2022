#include "PolygonMeshCreateCommand.h"

#include "../Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "PublicLabel.h"

namespace PolygonMeshCreateLabels
{
	PublicLabel CommandNameLabel = "PolygonMeshCreate";
	PublicLabel PositionsLabel = "Positions";
	PublicLabel NormalsLabel = "Normals";
	PublicLabel TexCoordsLabel = "TexCoords";
	PublicLabel NameLabel = "Name";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshCreateCommand::Args::Args() :
	positions(PolygonMeshCreateLabels::PositionsLabel, {}),
	normals(PolygonMeshCreateLabels::NormalsLabel, {}),
	texCoords(PolygonMeshCreateLabels::TexCoordsLabel, {}),
	name(PolygonMeshCreateLabels::NameLabel, std::string(""))
{
	add(&positions);
	add(&normals);
	add(&texCoords);
	add(&name);
}

PolygonMeshCreateCommand::Results::Results() :
	newId(PolygonMeshCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string PolygonMeshCreateCommand::getName()
{
	return ::PolygonMeshCreateLabels::CommandNameLabel;
}

bool PolygonMeshCreateCommand::execute(World* world)
{
	auto mesh = std::make_unique<PolygonMesh>();
	mesh->positions = args.positions.getValue();
	mesh->normals = args.normals.getValue();
	mesh->texCoords = args.texCoords.getValue();

	auto shape = new PolygonMeshScene(world->getNextSceneId(), args.name.getValue(), std::move(mesh));//world->getSceneFactory()->createPolygonMeshScene(std::move(mesh), args.name.getValue());
	world->addScene(shape);
	//auto group = (shape, "FaceGroup");
	const auto newId = shape->getId();

	//world->updateViewModel();

	results.newId.setValue(newId);

	return true;
}
