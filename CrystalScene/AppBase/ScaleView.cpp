#include "ScaleView.h"
#include "../Scene/IShapeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

ScaleView::ScaleView(const std::string& name, World* scene, Canvas* canvas) :
	IOkCancelView(name, scene, canvas),
	objectSelectView("Object", scene, canvas),
	scaleView("Scale", Vector3dd(1,1,1))
{
	add(&objectSelectView);
	add(&scaleView);
}

void ScaleView::onOk()
{
	const auto id = objectSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<IShapeScene*>(id);
	const auto& v = scaleView.getValue();
	const Matrix4dd matrix
	(
		v[0], 0.0, 0.0, 0.0,
		0.0, v[1], 0.0, 0.0,
		0.0, 0.0, v[2], 0.0,
		0.0, 0.0, 0.0, 1.0
	);
	scene->transform(matrix);
	//getWorld()->updateViewModel();

}
