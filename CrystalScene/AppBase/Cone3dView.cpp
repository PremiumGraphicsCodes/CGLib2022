#include "Cone3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Cone3dView::Cone3dView(const std::string& name) :
	IView(name),
	bottomView("Bottom", Math::Vector3dd(0, 0, 0)),
	radiusView("Radius", 1.0),
	heightView("Height", 1.0)
{
	add(&bottomView);
	add(&radiusView);
	add(&heightView);
}

Cone3d Cone3dView::getValue() const
{
	return Math::Cone3d(bottomView.getValue(), radiusView.getValue(), heightView.getValue());
}

void Cone3dView::setValue(const Cone3d& value)
{
	this->bottomView.setValue(value.getBottom());
	this->radiusView.setValue(value.getRadius());
	this->heightView.setValue(value.getHeight());
}
