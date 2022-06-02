#pragma once

#include "Vector3d.h"
#include "Matrix3d.h"
#include "Matrix4d.h"
#include "ICurve3d.h"

namespace Crystal {
	namespace Math {
		class Ray3d;

template<typename T>
class Line3d : public ICurve3d<T>
{
public:
	Line3d();

	Line3d(const Math::Vector3d<T>& origin, const Math::Vector3d<T>& dir);

	static Line3d<T> fromPoints(const Vector3d<T>& start, const Vector3d<T>& end);

	Math::Vector3d<T> getStart() const { return origin; }

	Math::Vector3d<T> getEnd() const { return origin + dir; }

	Math::Vector3d<T> getDirection() const { return dir; }

	T getLength() const { return glm::distance(origin, dir); }

	void move(const Math::Vector3d<T>& v) { this->origin += v; }

	void transform(const Math::Matrix3d<T>& m);

	void transform(const Math::Matrix4d<T>& m);

	Math::Vector3d<T> getPosition(const T u) const override;

	bool isSame(const Line3d<T>& rhs, const T tolerance) const;

	Ray3d toRay() const;

private:
	Math::Vector3d<T> origin;
	Math::Vector3d<T> dir;
};

using Line3dd = Line3d<double>;
	}
}