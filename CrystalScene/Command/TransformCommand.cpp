#include "TransformCommand.h"

#include "../Scene/IShapeScene.h"
#include "PublicLabel.h"

namespace TransformLabels
{
	PublicLabel TransformCommandLabel = "Transform";
	PublicLabel IdLabel = "Id";
	PublicLabel MatrixLabel = "Matrix";
}

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TransformCommand::Args::Args() :
	id(TransformLabels::IdLabel, -1),
	matrix(TransformLabels::MatrixLabel, Math::Matrix4dd())
{
	add(&id);
	add(&matrix);
}

std::string TransformCommand::getName()
{
	return TransformLabels::TransformCommandLabel;
}

bool TransformCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<Scene::IShapeScene*>(args.id.getValue());
	if (scene == nullptr) {
		return false;
	}
	scene->transform(args.matrix.getValue());
	return true;
}
