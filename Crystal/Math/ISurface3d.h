#pragma once

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class ISurface3d
{
public:
	virtual ~ISurface3d() = default;

	virtual Vector3d<T> getPosition(const T u, const T v) const = 0;

	virtual Vector3d<T> getNormal(const T u, const T v) const = 0;
};

using ISurface3dd = ISurface3d<double>;

	}
}
