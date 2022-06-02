#pragma once

#include "ICurve3d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Circle3d : public ICurve3d<T>
{
public:
	Circle3d();

	Circle3d(const Vector3d<T>& center, const Vector3d<T>& uvec, const Vector3d<T>& vvec);

	Vector3d<T> getPosition(const T u) const;

	Vector3d<T> getNormal() const;

	Vector3d<T> getCenter() const { return center; }

	Vector3d<T> getUVec() const { return uvec; }

	Vector3d<T> getVVec() const { return vvec; }

private:
	Vector3d<T> center;
	Vector3d<T> uvec;
	Vector3d<T> vvec;
};


using Circle3dd = Circle3d<double>;

	}
}
