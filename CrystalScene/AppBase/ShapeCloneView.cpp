#include "ShapeCloneView.h"

#include "../Scene/IShapeScene.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ShapeCloneView::ShapeCloneView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	shapeSelectView("Shape", model, canvas)
{}

void ShapeCloneView::onOk()
{
	auto shape = getWorld()->getScenes()->findSceneById<IShapeScene*>( shapeSelectView.getId() );
	//shape->clone();
}