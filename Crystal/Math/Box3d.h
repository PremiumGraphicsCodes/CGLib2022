#pragma once

#include "Vector3d.h"
#include "IVolume3d.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Sphere3d;

template<typename T>
class Box3d : public IVolume3d<T>
{
public:
	Box3d();

	explicit Box3d(const Vector3d<T>& point);

	Box3d(const Vector3d<T>& pointX, const Vector3d<T>& pointY);

	Box3d<T> getBoundingBox() const { return *this; }

	static Box3d<T> createDegeneratedBox();

	bool isDegenerated() const;

	void add(const Vector3d<T>& v);

	void add(const Box3d<T>& b);

	T getVolume() const;

	Vector3d<T> getMax() const { return max; }

	Vector3d<T> getMin() const { return min; }

	Vector3d<T> getStart() const { return getMin(); }

	Vector3d<T> getEnd() const { return getMax(); }

	Vector3d<T> getCenter() const;

	bool isInside(const Vector3d<T>& point) const;

	bool isOutside(const Vector3d<T>& point) const { return !isInside(point); }

	bool contains(const Vector3d<T>& position, const T tolerance) const;

	T getMaxX() const { return max.x; }

	T getMinX() const { return min.x; }

	T getMaxY() const { return max.y; }

	T getMinY() const { return min.y; }

	T getMaxZ() const { return max.z; }

	T getMinZ() const { return min.z; }

	Vector3d<T> getLength() const { return Vector3d<T>(max.x - getMinX(), max.y - getMinY(), max.z - getMinZ()); }

	bool isSame(const Box3d<T>& rhs, const T tolerance) const;

	bool hasIntersection(const Box3d<T>& rhs) const;

	Box3d<T> getOverlapped(const Box3d<T>& rhs) const;

	Vector3d<T> getPosition(const T u, const T v, const T w) const override;

	Sphere3d<T> getBoundingSphere() const;

	bool isDegenerated(const T tolerance) { return getVolume() < tolerance; }

	void translate(const Math::Vector3d<T>& v);

private:
	Vector3d<T> min;
	Vector3d<T> max;
};

using Box3df = Box3d<float>;
using Box3dd = Box3d<double>;

	}
}