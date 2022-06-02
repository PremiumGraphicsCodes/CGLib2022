#include "Box3d.h"
#include "Sphere3d.h"

#include <numeric>

using namespace Crystal::Math;

template<typename T>
Box3d<T>::Box3d() :
	min(0, 0, 0),
	max(1, 1, 1)
{
}

template<typename T>
Box3d<T>::Box3d(const Vector3d<T>& point) :
	min(point),
	max(point)
{}

template<typename T>
Box3d<T>::Box3d(const Vector3d<T>& pointX, const Vector3d<T>& pointY)
{
	const auto x = std::min<T>(pointX.x, pointY.x);
	const auto y = std::min<T>(pointX.y, pointY.y);
	const auto z = std::min<T>(pointX.z, pointY.z);
	this->min = Vector3dd(x, y, z);
	const auto endX = std::max<T>(pointX.x, pointY.x);
	const auto endY = std::max<T>(pointX.y, pointY.y);
	const auto endZ = std::max<T>(pointX.z, pointY.z);
	this->max = Vector3dd(endX, endY, endZ);
//	assert(isValid());
}

template<typename T>
Box3d<T> Box3d<T>::createDegeneratedBox()
{
	Box3d<T> b;
	constexpr auto min = std::numeric_limits<T>::lowest();
	constexpr auto max = std::numeric_limits<T>::max();
	b.max = Vector3dd(min, min, min);
	b.min = Vector3dd(max, max, max);
	return b;
}

template<typename T>
bool Box3d<T>::isDegenerated() const
{
	const Box3d b = createDegeneratedBox();
	return b.getMax() == this->getMax() && b.getMin() == this->getMin();
}

template<typename T>
void Box3d<T>::add(const Vector3d<T>& v)
{
	const auto x = std::min<T>(getMinX(), v.x);
	const auto y = std::min<T>(getMinY(), v.y);
	const auto z = std::min<T>(getMinZ(), v.z);
	min = Vector3d<T>(x, y, z);

	const auto endX = std::max<T>(max.x, v.x);
	const auto endY = std::max<T>(max.y, v.y);
	const auto endZ = std::max<T>(max.z, v.z);
	max = Vector3d<T>(endX, endY, endZ);
}

template<typename T>
void Box3d<T>::add(const Box3d<T>& b)
{
	const auto sx = std::min<T>(getMinX(), b.getMinX());
	const auto sy = std::min<T>(getMinY(), b.getMinY());
	const auto sz = std::min<T>(getMinZ(), b.getMinZ());
	this->min = Vector3d<T>(sx, sy, sz);

	const auto ex = std::max<T>(max.x, b.getMaxX());
	const auto ey = std::max<T>(max.y, b.getMaxY());
	const auto ez = std::max<T>(max.z, b.getMaxZ());
	this->max = Vector3d<T>(ex, ey, ez);
}

template<typename T>
T Box3d<T>::getVolume() const
{
	const auto& length = getLength();
	return length.x * length.y * length.z;
}

template<typename T>
Vector3d<T> Box3d<T>::getCenter() const
{
	return Vector3d<T>(
		(getMinX() + max.x) / 2.0,
		(getMinY() + max.y) / 2.0,
		(getMinZ() + max.z) / 2.0
	);
}

template<typename T>
bool Box3d<T>::isInside(const Vector3d<T>& point) const
{
	const bool xIsInterior = (getMinX() < point.x && point.x < max.x);
	const bool yIsInterior = (getMinY() < point.y && point.y < max.y);
	const bool zIsInterior = (getMinZ() < point.z && point.z < max.z);
	return xIsInterior && yIsInterior && zIsInterior;
}

template<typename T>
bool Box3d<T>::contains(const Vector3d<T>& point, const T tolerance) const
{
	const bool xIsInterior = (min.x - tolerance < point.x && point.x < max.x + tolerance);
	const bool yIsInterior = (min.y - tolerance < point.y && point.y < max.y + tolerance);
	const bool zIsInterior = (min.z - tolerance < point.z && point.z < max.z + tolerance);
	return xIsInterior && yIsInterior && zIsInterior;
}

template<typename T>
bool Box3d<T>::isSame(const Box3d<T>& rhs, const T tolerance) const
{
	return
		areSame( min, rhs.getStart(), tolerance ) &&
		areSame( max, rhs.getEnd(), tolerance );
}

template<typename T>
bool Box3d<T>::hasIntersection(const Box3d<T>& rhs) const
{
	const auto distx = std::fabs(getCenter().x - rhs.getCenter().x);
	const auto lx = getLength().x / 2.0 + rhs.getLength().x / 2.0;

	const auto disty = std::fabs(getCenter().y - rhs.getCenter().y);
	const auto ly = getLength().y / 2.0 + rhs.getLength().y / 2.0;

	const auto distz = std::fabs(getCenter().z - rhs.getCenter().z);
	const auto lz = getLength().z / 2.0 + rhs.getLength().z / 2.0;

	return (distx < lx && disty < ly && distz < lz);
}

template<typename T>
Box3d<T> Box3d<T>::getOverlapped(const Box3d<T>& rhs) const
{
	assert(hasIntersection(rhs));
	const auto minx = std::max<T>(this->getStart().x, rhs.getStart().x);
	const auto miny = std::max<T>(this->getStart().y, rhs.getStart().y);
	const auto minz = std::max<T>(this->getStart().z, rhs.getStart().z);

	const auto maxx = std::min<T>(this->getEnd().x, rhs.getEnd().x);
	const auto maxy = std::min<T>(this->getEnd().y, rhs.getEnd().y);
	const auto maxz = std::min<T>(this->getEnd().z, rhs.getEnd().z);

	const Vector3d<T> min_(minx, miny, minz);
	const Vector3d<T> max_(maxx, maxy, maxz);
	return Box3d<T>(min_, max_);
}

template<typename T>
Vector3d<T> Box3d<T>::getPosition(const T u, const T v, const T w) const
{
	const auto& length = getLength();
	const auto x = min.x + length.x * u;
	const auto y = min.y + length.y * v;
	const auto z = min.z + length.z * w;
	return Vector3d<T>(x, y, z);
}

template<typename T>
Sphere3d<T> Box3d<T>::getBoundingSphere() const
{
	const auto& halfLength = getLength() * T(0.5);
	const auto radius = glm::length(halfLength);
	return Sphere3d(getCenter(), radius);
}

template<typename T>
void Box3d<T>::translate(const Math::Vector3d<T>& v)
{
	this->min += v;
	this->max += v;
}

template class Box3d<float>;
template class Box3d<double>;