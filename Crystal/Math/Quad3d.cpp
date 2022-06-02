#include "Quad3d.h"

#include "Plane3d.h"

using namespace Crystal::Math;

Quad3d::Quad3d() :
	Quad3d(Vector3dd(0,0,0), Vector3dd(1,0,0), Vector3dd(0,1,0))
{}

Quad3d::Quad3d(const Vector3dd& origin, const Vector3dd& uvec, const Vector3dd& vvec) :
	origin(origin),
	uvec(uvec),
	vvec(vvec)
{
}

Vector3dd Quad3d::getPosition(const double u, const double v) const
{
	return origin + uvec * u + vvec * v;
}

Vector3dd Quad3d::getNormal() const
{
	return glm::normalize(glm::cross(uvec, vvec));
}

Vector3dd Quad3d::getNormal(const double u, const double v) const
{
	return getNormal();
}

bool Quad3d::isInside(const Vector3dd& p) const
{
	const auto& n = getNormal();

	const auto a = getV0() - p;
	const auto b = getV1() - p;
	const auto c = getV2() - p;
	const auto d = getV3() - p;

	const auto aa = getV1() - getV0();
	const auto bb = getV2() - getV1();
	const auto cc = getV3() - getV2();
	const auto dd = getV0() - getV3();

	const auto& v1 = glm::cross(a, aa);
	if (glm::dot(v1, n) < 0.0) {
		return false;
	}
	const auto& v2 = glm::cross(b, bb);
	if (glm::dot(v2, n) < 0.0) {
		return false;
	}
	const auto& v3 = glm::cross(c, cc);
	if (glm::dot(v3, n) < 0.0) {
		return false;
	}
	const auto& v4 = glm::cross(d, dd);
	if (glm::dot(v4, n) < 0.0) {
		return false;
	}
	return true;
}

Plane3d Quad3d::toPlane() const
{
	return Plane3d(origin, getNormal());
}

bool Quad3d::isSame(const Quad3d& rhs, const double tolerance) const
{
	return
		areSame(origin, rhs.origin, tolerance) &&
		areSame(uvec, rhs.uvec, tolerance) &&
		areSame(vvec, rhs.vvec, tolerance);
}
