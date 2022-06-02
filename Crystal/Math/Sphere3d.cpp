#include "Sphere3d.h"
#include "Box3d.h"

#include <numeric>
#include "Tolerance.h"

using namespace Crystal::Math;

template<typename T>
Sphere3d<T>::Sphere3d() :
	center(Vector3dd(0, 0, 0)),
	radius(1.0)
{}

template<typename T>
Sphere3d<T>::Sphere3d(const Vector3d<T>& center, const T radius) :
	center(center),
	radius(radius)
{}

template<typename T>
Sphere3d<T>::Sphere3d(const Box3d<T>& boundingBox)
{
	center = boundingBox.getCenter();
	const auto& length = boundingBox.getLength();
	radius = std::min<T>(std::min<T>(length.x, length.y), length.z) * T(0.5);
}

template<typename T>
Vector3d<T> Sphere3d<T>::getPosition(const T u, const T v) const
{
	return getPosition(u, v, 1.0);
}

template<typename T>
Vector3d<T> Sphere3d<T>::getPosition(const T u, const T v, const T w) const
{
	const auto theta = u * PI;
	const auto phi = 2.0 * v * PI;
	const auto x = w * radius * std::sin(theta) * std::cos(phi);
	const auto y = w * radius * std::sin(theta) * std::sin(phi);
	const auto z = w * radius * std::cos(theta);
	return center + Vector3d<T>(x, y, z);
}

template<typename T>
Vector3d<T> Sphere3d<T>::getNormal(const T u, const T v) const
{
	const auto& pos = getPosition(u, v, 1.0);
	return glm::normalize(pos - center);
}

template<typename T>
bool Sphere3d<T>::isSame(const Sphere3d<T>& rhs, const T tolerance) const
{
	return
		::isEqual(radius, rhs.radius, tolerance) &&
		(center == rhs.center);
}

template<typename T>
Box3d<T> Sphere3d<T>::getBoundingBox() const
{
	const auto min = center - Vector3d<T>(radius, radius, radius);
	const auto max = center + Vector3d<T>(radius, radius, radius);
	return Box3d<T>(min, max);
}

template class Sphere3d<float>;
template class Sphere3d<double>;