#include "Ray3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Ray3dView::Ray3dView(const std::string& name) :
	IView(name),
	originView("Origin", Math::Vector3dd(0, 0, 0)),
	directionView("Direction", Math::Vector3dd(0, 0, 1))
{
	add(&originView);
	add(&directionView);
}

Ray3d Ray3dView::getValue() const
{
	return Math::Ray3d(originView.getValue(), directionView.getValue());
}
