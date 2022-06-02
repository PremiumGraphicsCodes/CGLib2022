#include "Circle3d.h"

#include "Tolerance.h"

#include <cmath>

using namespace Crystal::Math;

template<typename T>
Circle3d<T>::Circle3d() :
	center(Vector3dd(0,0,0)),
	uvec(Vector3dd(1,0,0)),
	vvec(Vector3dd(0,1,0))
{}

template<typename T>
Circle3d<T>::Circle3d(const Vector3d<T>& center, const Vector3d<T>& uvec, const Vector3d<T>& vvec) :
	center(center),
	uvec(uvec),
	vvec(vvec)
{}

template<typename T>
Vector3d<T> Circle3d<T>::getPosition(const T u) const
{
	const auto uu = u * T(2.0) * T(PI);
	return center + ::cos(uu) * uvec + ::sin(uu) * vvec;
}

template<typename T>
Vector3d<T> Circle3d<T>::getNormal() const
{
	return glm::normalize( glm::cross(uvec, vvec) );
}


template class Circle3d<float>;
template class Circle3d<double>;