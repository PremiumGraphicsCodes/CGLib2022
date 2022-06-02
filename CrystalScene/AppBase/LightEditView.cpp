#include "LightEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

LightEditView::LightEditView(const std::string& name, World* world, Canvas* canvas) :
	IEditCancelView(name, world, canvas),
	idView("Id", 0),
	lightView("Light"),
	nameView("Name", "")
{
	add(&idView);
	add(&lightView);
	add(&nameView);
}

void LightEditView::setValue(LightScene* value)
{
	this->idView.setValue(value->getId());
	this->nameView.setValue(value->getName());
	this->lightView.position.setValue(value->getLight()->getPosition());
	this->lightView.ambient.setValue(value->getLight()->getAmbient());
	this->lightView.diffuse.setValue(value->getLight()->getDiffuse());
	this->lightView.specular.setValue(value->getLight()->getSpecular());
}

void LightEditView::onEdit()
{
	auto light = getWorld()->getScenes()->findSceneById<LightScene*>(idView.getValue());
	auto l = light->getLight();
	l->setPosition(lightView.position.getValue());
	l->setAmbient(lightView.ambient.getValue());
	l->setDiffuse(lightView.diffuse.getValue());
	l->setSpecular(lightView.specular.getValue());
}
