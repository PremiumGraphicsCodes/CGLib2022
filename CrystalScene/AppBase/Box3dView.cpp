#include "Box3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Box3dView::Box3dView(const std::string& name) :
	IView(name),
	minView("Min", Vector3dd(0, 0, 0)),
	maxView("Max", Vector3dd(1, 1, 1))
{
	add(&minView);
	add(&maxView);
}

Box3dView::Box3dView(const std::string& name, const Box3dd& value) :
	IView(name),
	minView("Min", value.getMin()),
	maxView("Max", value.getMax())
{
	add(&minView);
	add(&maxView);
}

Box3dd Box3dView::getValue() const
{
	return Box3dd(minView.getValue(), maxView.getValue());
}

void Box3dView::setValue(const Box3dd& value)
{
	minView.setValue(value.getMin());
	maxView.setValue(value.getMax());
}