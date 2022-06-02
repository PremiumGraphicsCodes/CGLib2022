#include "Line3d.h"
#include "Ray3d.h"

using namespace Crystal::Math;

template<typename T>
Line3d<T>::Line3d() :
	origin(0, 0, 0),
	dir(1, 0, 0)
{
}

template<typename T>
Line3d<T>::Line3d(const Vector3d<T>& origin, const Vector3d<T>& dir) :
	origin(origin),
	dir(dir)
{
}

template<typename T>
Line3d<T> Line3d<T>::fromPoints(const Vector3d<T>& start, const Vector3d<T>& end)
{
	return Line3d<T>(start, end - start);
}

template<typename T>
void Line3d<T>::transform(const Matrix3d<T>& m)
{
	origin = m * origin;
	dir = m * dir;
}

template<typename T>
void Line3d<T>::transform(const Matrix4d<T>& m)
{
	origin = m * glm::vec4(origin, 1.0);
	dir = m * glm::vec4(dir, 1.0);
}

template<typename T>
Vector3d<T> Line3d<T>::getPosition(const T u) const
{
	return origin + dir * u;
}

template<typename T>
bool Line3d<T>::isSame(const Line3d<T>& rhs, const T tolerance) const
{
	return
		areSame(origin, rhs.getStart(), tolerance) &&
		areSame(dir, rhs.getDirection(), tolerance);
}

template<typename T>
Ray3d Line3d<T>::toRay() const
{
	const auto& direction = glm::normalize(getDirection());
	return Ray3d(origin, direction);
}

template class Line3d<double>;