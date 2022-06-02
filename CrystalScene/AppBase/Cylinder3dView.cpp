#include "Cylinder3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Cylinder3dView::Cylinder3dView(const std::string& name) :
	IView(name),
	centerView("Center", Math::Vector3dd(0, 0, 0)),
	radiusView("Radius", 1.0),
	heightView("Height", 1.0)
{
	add(&centerView);
	add(&radiusView);
	add(&heightView);
}

Cylinder3d Cylinder3dView::getValue() const
{
	return Math::Cylinder3d(radiusView.getValue(), heightView.getValue(), centerView.getValue());
}

void Cylinder3dView::setValue(const Cylinder3d& value)
{
	centerView.setValue(value.getCenter());
	radiusView.setValue(value.getRadius());
	heightView.setValue(value.getHeight());
}
