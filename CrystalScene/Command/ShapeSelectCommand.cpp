#include "ShapeSelectCommand.h"
#include "../Scene/IShapeScene.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../Scene/WireFrameScene.h"

#include "PublicLabel.h"

namespace ShapeSelectLabels
{
	PublicLabel CommandNameLabel = "ShapeSelectCommand";
	PublicLabel ShapeIdLabel = "ShapeId";
}

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::Command;

std::string ShapeSelectCommand::getName()
{
	return ShapeSelectLabels::CommandNameLabel;
}

ShapeSelectCommand::Args::Args() :
	shapeId(ShapeSelectLabels::ShapeIdLabel, -1)
{
	add(&shapeId);
}

ShapeSelectCommand::Results::Results() // :
//	boundingBoxItemId(ShapeSelectLabels::BoundingBoxItemIdLabel, -1)
{
//	add(&boundingBoxItemId);
}

bool ShapeSelectCommand::execute(World* scene)
{
	const auto shapeId = args.shapeId.getValue();
	if (shapeId == 0) {
		return false;
	}
	auto shape = scene->getScenes()->findSceneById<IShapeScene*>(shapeId);
	if (shape == nullptr) {
		return false;
	}

	return true;
}