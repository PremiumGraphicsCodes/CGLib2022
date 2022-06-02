#include "Ellipsoid3d.h"

#include "Box3d.h"

#include "Sphere3d.h"

using namespace Crystal::Math;

Ellipsoid3d::Ellipsoid3d() :
	center(0,0,0),
	uvec(1,0,0),
	vvec(0,1,0),
	wvec(0,0,1)
{}

Ellipsoid3d::Ellipsoid3d(const Vector3dd& center, const Vector3dd& uvec, const Vector3dd& vvec, const Vector3dd& wvec) :
	center(center),
	uvec(uvec),
	vvec(vvec),
	wvec(wvec)
{
}

Vector3dd Ellipsoid3d::getPosition(const double u, const double v) const
{
	Sphere3d s(Vector3dd(0,0,0), 1.0);
	const auto p = s.getPosition(u, v);
	auto uu = p.x * uvec;
	auto vv = p.y * vvec;
	auto ww = p.z * wvec;
	return center + uu + vv + ww;
}

Vector3dd Ellipsoid3d::getNormal(const double u, const double v) const
{
	return Vector3dd(0, 0, 0);
}

bool Ellipsoid3d::isSame(const Ellipsoid3d& rhs, const double tolerance) const
{
	return
		areSame(center, rhs.center, tolerance) &&
		areSame(uvec, rhs.uvec, tolerance) &&
		areSame(vvec, rhs.vvec, tolerance) &&
		areSame(wvec, rhs.wvec, tolerance);
}

Box3dd Ellipsoid3d::getBoundingBox() const
{
	Box3dd bb(getPosition(0, 0));
	bb.add(getPosition(1, 1));
	return bb;
}