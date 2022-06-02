#include "ParticleSystemEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

ParticleSystemEditView::ParticleSystemEditView(const std::string& name, World* world, Canvas* canvas) :
	IEditCancelView(name, world, canvas),
	idView("Id"),
	attributeView("Attribute"),
	presenterView("Presenter")
{
	add(&idView);
	add(&presenterView);
}

void ParticleSystemEditView::setValue(ParticleSystemScene* value)
{
	this->idView.setValue(value->getId());
	//this->attributeView.setName(value->get)
}

void ParticleSystemEditView::onEdit()
{
	auto particleSystem = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>( idView.getValue() );
	//particleSystem->setName(attributeView.getName());
	particleSystem->setAttribute(attributeView.getValue());
	//getWorld()->updateViewModel();
	//particleSystem->setAttribute();
}
