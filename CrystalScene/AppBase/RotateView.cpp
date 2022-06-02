#include "RotateView.h"
#include "../Scene/IShapeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

RotateView::RotateView(const std::string& name, World* scene, Canvas* canvas) :
	IOkCancelView(name, scene, canvas),
	objectSelectView("Object", scene, canvas),
	matrixView("Matrix")
{
	add(&objectSelectView);
	add(&matrixView);
}

void RotateView::onOk()
{
	auto shape = getWorld()->getScenes()->findSceneById<IShapeScene*>( objectSelectView.getId() );
	if (shape == nullptr) {
		return;
	}
	const auto& matrix = matrixView.getValue();
	shape->transform(matrix);
	//model->updateViewModel();
}