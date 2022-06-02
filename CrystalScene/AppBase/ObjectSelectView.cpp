#include "ObjectSelectView.h"

#include "imgui.h"
#include "PickUICtrl.h"
#include "CameraUICtrl.h"

using namespace Crystal::UI;
using namespace Crystal::Scene;

ObjectSelectView::ObjectSelectView(const std::string& name, World* model, Canvas* canvas) :
	ObjectSelectView(name, model, canvas, Scene::SceneTypeLabels::ParticleSystemScene)
{
}

ObjectSelectView::ObjectSelectView(const std::string& name, World* model, Canvas* canvas, const SceneType type) :
	IView(name),
	idView("Id", 0),
	pickButton("Pick"),
	type(type)
{
	pickButton.setFunction([=]() { onPick(model, canvas); });
	add(&idView);
	add(&pickButton);
}

void ObjectSelectView::onPick(World* model, Canvas* canvas)
{
	auto ctrl = new PickUICtrl(model, canvas, type, 0.01f);
	auto func = [=](int parentId, int childId) { this->idView.setValue(parentId); };
	ctrl->setFunction(func);
	canvas->setUICtrl(ctrl);

}