#include "Box3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Box3dfView::Box3dfView(const std::string& name) :
	IView(name),
	minView("Min", Vector3df(0, 0, 0)),
	maxView("Max", Vector3df(1, 1, 1))
{
	add(&minView);
	add(&maxView);
}

Box3dfView::Box3dfView(const std::string& name, const Box3df& value) :
	IView(name),
	minView("Min", value.getMin()),
	maxView("Max", value.getMax())
{
	add(&minView);
	add(&maxView);
}

Box3df Box3dfView::getValue() const
{
	return Box3df(minView.getValue(), maxView.getValue());
}

void Box3dfView::setValue(const Box3df& value)
{
	minView.setValue(value.getMin());
	maxView.setValue(value.getMax());
}

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