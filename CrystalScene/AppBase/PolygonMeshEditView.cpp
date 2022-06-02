#include "PolygonMeshEditView.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonMeshEditView::PolygonMeshEditView(const std::string& name, World* repository, Canvas* canvas) :
	IView(name),
	presenterView("Presenter"),
	world(repository),
	idView("Id"),
	nameView("Name"),
	editButton("Edit")
{
	add(&presenterView);
	add(&idView);
	add(&nameView);
	add(&editButton);
	editButton.setFunction([=]() { onEdit(); });
}

void PolygonMeshEditView::setValue(PolygonMeshScene* value)
{
	idView.setValue(value->getId());
	nameView.setValue(value->getName());
}

void PolygonMeshEditView::onEdit()
{
	auto scene = world->getScenes()->findSceneById<PolygonMeshScene*>(idView.getValue());
	if (scene == nullptr) {
		return;
	}
	scene->setName(nameView.getValue());

	scene->getPresenter()->removeView(world->getRenderer());
	presenterView.setPresenter(scene, world);
}