#pragma once

#include "Vector3d.h"
#include "IVolume3d.h"
#include "ISurface3d.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Box3d;

template<typename T>
class Sphere3d : public ISurface3d<T>, public IVolume3d<T>
{
public:
	Sphere3d();

	Sphere3d(const Vector3d<T>& center, const T radius);

	explicit Sphere3d(const Math::Box3d<T>& boundingBox);

	Vector3d<T> getPosition(const T u, const T v) const override;

	Vector3d<T> getPosition(const T u, const T v, const T w) const override;

	Vector3d<T> getNormal(const T u, const T v) const override;

	Vector3d<T> getCenter() const { return center; }

	T getRadius() const { return radius; }

	bool isValid(const T tolerance) const { return radius >= tolerance;  }

	void outerOffset(const T offsetLength) { this->radius += offsetLength; }

	void innerOffset(const T offsetLength) { this->radius -= offsetLength; }

	bool isSame(const Sphere3d<T>& rhs, const T tolerance) const;

	bool isInside(const Vector3d<T>& v) const { return glm::distance(v, center) < radius; }

	bool isOutside(const Vector3d<T>& v) const { return glm::distance(v, center) > radius; }

	void moveTo(const Vector3dd& pos) { this->center = pos; }

	Box3d<T> getBoundingBox() const;

private:
	Vector3d<T> center;
	T radius;
};

using Sphere3df = Sphere3d<float>;
using Sphere3dd = Sphere3d<double>;
	}
}
