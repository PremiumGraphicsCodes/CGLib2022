#pragma once

#include "Vector2d.h"
//#include "ISurface3d.h"
#include <array>

namespace Crystal {
	namespace Math {

template<typename T>
class Box2d //: ICurve2d
{
public:
	Box2d() :
		start(Vector2d<T>(0, 0)),
		end(Vector2d<T>(1, 1))
	{}

	Box2d(const Vector2d<T>& pointX, const Vector2d<T>& pointY);

	void add(const Vector2d<T>& v);

	void add(const Box2d<T>& b);

	T getArea() const { return (end.x - getMinX()) * (end.y - getMinY());  }

	Vector2d<T> getMax() const { return Vector2d<T>(end[0], end[1]); }

	Vector2d<T> getMin() const { return Vector2d<T>(getMinX(), getMinY()); }

	Vector2d<T> getStart() const { return getMin(); }

	Vector2d<T> getEnd() const { return getMax(); }

	Vector2d<T> getCenter() const;

	//std::vector< Vector2d<T> > toInnerPoints(const T divideLength) const;

	T getMaxX() const { return end[0]; }

	T getMinX() const { return start[0]; }

	T getMaxY() const { return end[1]; }

	T getMinY() const { return start[1]; }

	Vector2d<T> getLength() const { return Vector2d<T>(end.x - getMinX(), end.y - getMinY()); }

	bool isValid() const { return (getMinX() <= end.x) && (getMinY() <= end.y); }

	bool isShirinked() const { return (getMinX() == end.x) && (getMinY() == end.y); }

	bool isSame(const Box2d<T>& rhs, const T tolerance) const;

	bool hasIntersection(const Box2d<T>& rhs) const;

	Box2d<T> getOverlapped(const Box2d<T>& rhs) const;

	std::array< T, 8 > toArray() const;

private:
	Vector2d<T> start;
	Vector2d<T> end;
};

using Box2df = Box2d<float>();

	}
}