#include "Circle3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Circle3dView::Circle3dView(const std::string& name) :
	IView(name),
	centerView("Center", Vector3dd(0,0,0)),
	uvecView("UVec", Vector3dd(1,0,0)),
	vvecView("VVec", Vector3dd(0,1,0))
{
	add(&centerView);
	add(&uvecView);
	add(&vvecView);
}

Circle3dd Circle3dView::getValue() const
{
	return Circle3dd(centerView.getValue(), uvecView.getValue(), vvecView.getValue());
}

void Circle3dView::setValue(const Circle3dd& value)
{
	this->centerView.setValue(value.getCenter());
	this->uvecView.setValue(value.getUVec());
	this->vvecView.setValue(value.getVVec());
}
