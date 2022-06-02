#include "LightView.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

LightView::LightView(const std::string& name) :
	IView(name),
	position("Position", Math::Vector3dd(0, 0, 0)),
	ambient("Ambient", glm::vec4(0, 0, 0, 0)),
	diffuse("Diffuse", glm::vec4(0, 0, 0, 0)),
	specular("Specular", glm::vec4(0, 0, 0, 0))
{
	add(&position);
	add(&ambient);
	add(&diffuse);
	add(&specular);
}

void LightView::setValue(const PointLight& value)
{
	this->position.setValue(value.getPosition());
	this->ambient.setValue(value.getAmbient());
	this->diffuse.setValue(value.getDiffuse());
	this->specular.setValue(value.getSpecular());
}

PointLight LightView::getValue() const
{
	PointLight l;
	l.setPosition(this->position.getValue());
	l.setAmbient(this->ambient.getValue());
	l.setDiffuse(this->diffuse.getValue());
	l.setSpecular(this->specular.getValue());
	return l;
}
