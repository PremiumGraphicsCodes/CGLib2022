#include "SpotLightView.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

SpotLightView::SpotLightView(const std::string& name) :
	IView(name),
	position("Position", Math::Vector3dd(0, 0, 0)),
	direction("Direction", Math::Vector3dd(1,0,0)),
	ambient("Ambient", glm::vec4(0, 0, 0, 0)),
	diffuse("Diffuse", glm::vec4(0, 0, 0, 0)),
	specular("Specular", glm::vec4(0, 0, 0, 0))
{
	add(&position);
	add(&direction);
	add(&ambient);
	add(&diffuse);
	add(&specular);
}

void SpotLightView::setValue(const SpotLight& value)
{
	this->position.setValue(value.getPosition());
	this->direction.setValue(value.getDirection());
	this->ambient.setValue(value.getAmbient());
	this->diffuse.setValue(value.getDiffuse());
	this->specular.setValue(value.getSpecular());
}

SpotLight SpotLightView::getValue() const
{
	SpotLight l;
	l.setPosition(this->position.getValue());
	l.setDirection(this->direction.getValue());
	l.setAmbient(this->ambient.getValue());
	l.setDiffuse(this->diffuse.getValue());
	l.setSpecular(this->specular.getValue());
	return l;
}