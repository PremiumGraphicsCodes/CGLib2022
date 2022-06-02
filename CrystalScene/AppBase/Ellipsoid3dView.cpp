#include "Ellipsoid3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Ellipsoid3dView::Ellipsoid3dView(const std::string& name) :
	IView(name),
	center("Center", Vector3dd(0, 0, 0)),
	uvec("UVec", Vector3dd(1,0,0)),
	vvec("VVec", Vector3dd(0,1,0)),
	wvec("WVec", Vector3dd(0,0,1))
{
	add(&center);
	add(&uvec);
	add(&vvec);
	add(&wvec);
}

Ellipsoid3d Ellipsoid3dView::getValue() const
{
	return Math::Ellipsoid3d(center.getValue(), uvec.getValue(), vvec.getValue(), wvec.getValue());
}

void Ellipsoid3dView::setValue(const Ellipsoid3d& value)
{
	this->center.setValue(value.getCenter());
	this->uvec.setValue(value.getUVec());
	this->vvec.setValue(value.getVVec());
	this->wvec.setValue(value.getWVec());
}

