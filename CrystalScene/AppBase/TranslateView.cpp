#include "TranslateView.h"
#include "../Scene/IShapeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

TranslateView::TranslateView(const std::string& name, World* scene, Canvas* canvas) :
	IOkCancelView(name, scene, canvas),
	objectSelectView("Object", scene, canvas),
	translateView("Translate", Vector3dd(0,0,0))
{
	add(&objectSelectView);
	add(&translateView);
}

void TranslateView::onOk()
{
	const auto id = objectSelectView.getId();
	auto shape = getWorld()->getScenes()->findSceneById<IShapeScene*>(id);
	const auto& v = translateView.getValue();
	const Matrix4dd matrix
	(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		v[0], v[1], v[2], 1.0
	);
	shape->transform(matrix);
	//getWorld()->updateViewModel();
}
