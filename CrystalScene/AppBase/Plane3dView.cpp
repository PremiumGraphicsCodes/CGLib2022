#include "Plane3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Plane3dView::Plane3dView(const std::string& name) :
	IView(name),
	originView("Origin", Math::Vector3dd(0, 0, 0)),
	normalView("Normal", Math::Vector3dd(0, 0, 1))
{
	add(&originView);
	add(&normalView);
}

Plane3d Plane3dView::getValue() const
{
	return Math::Plane3d(originView.getValue(), normalView.getValue());
}

void Plane3dView::setValue(const Plane3d& value)
{
	originView.setValue( value.getOrigin() );
	normalView.setValue( value.getNormal() );
}
