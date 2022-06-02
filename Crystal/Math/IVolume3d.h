#pragma once

#include "Vector2d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class IVolume3d
{
public:
	virtual ~IVolume3d() = default;

	virtual Vector3d<T> getPosition(const T u, const T v, const T w) const = 0;

	virtual bool isInside(const Math::Vector3d<T>& position) const = 0;
};

using IVolume3dd = IVolume3d<double>;

	}
}
