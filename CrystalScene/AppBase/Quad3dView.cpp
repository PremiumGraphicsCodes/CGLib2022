#include "Quad3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Quad3dView::Quad3dView(const std::string& name) :
	IView(name),
	originView("Origin", Math::Vector3dd(0, 0, 0)),
	uvecView("UVec", Math::Vector3dd(1, 0, 0)),
	vvecView("VVec", Math::Vector3dd(0, 1, 0))
{
	add(&originView);
	add(&uvecView);
	add(&vvecView);
}

Quad3d Quad3dView::getValue() const
{
	return Math::Quad3d(originView.getValue(), uvecView.getValue(), vvecView.getValue());
}
