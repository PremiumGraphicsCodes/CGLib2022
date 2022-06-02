#include "Box2d.h"

using namespace Crystal::Math;

template<typename T>
Box2d<T>::Box2d(const Vector2d<T>& pointX, const Vector2d<T>& pointY)
{
	const auto x = std::min<T>(pointX.x, pointY.x);
	const auto y = std::min<T>(pointX.y, pointY.y);
	this->start = Vector2d<T>(x, y);
	const auto endX = std::max<T>(pointX.x, pointY.x);
	const auto endY = std::max<T>(pointX.y, pointY.y);
	this->end = Vector2d<T>(endX, endY);
}

template<typename T>
void Box2d<T>::add(const Vector2d<T>& v)
{
	const auto x = std::min<T>(getMinX(), v.x);
	const auto y = std::min<T>(getMinY(), v.y);
	start = Vector2df(x, y);

	const auto endX = std::max<T>(end.x, v.x);
	const auto endY = std::max<T>(end.y, v.y);
	end = Vector2df(endX, endY);
}

template<typename T>
void Box2d<T>::add(const Box2d<T>& b)
{
	const auto sx = std::min<T>(getMinX(), b.getMinX());
	const auto sy = std::min<T>(getMinY(), b.getMinY());
	this->start = Vector2df(sx, sy);

	const auto ex = std::max<T>(end.x, b.getMaxX());
	const auto ey = std::max<T>(end.y, b.getMaxY());
	this->end = Vector2df(ex, ey);
}

template<typename T>
Vector2d<T> Box2d<T>::getCenter() const {
	return Vector2d<T>(
		(getMinX() + end.x) / 2.0f,
		(getMinY() + end.y) / 2.0f
	);
}

template<typename T>
bool Box2d<T>::isSame(const Box2d<T>& rhs, const T tolerance) const
{
	return
		areSame(start, rhs.start, tolerance) &&
		areSame(end, rhs.end, tolerance);
}

template<typename T>
bool Box2d<T>::hasIntersection(const Box2d<T>& rhs) const
{
	const auto distx = std::fabs(getCenter().x - rhs.getCenter().x);
	const auto lx = getLength().x / 2.0f + rhs.getLength().x / 2.0f;

	const auto disty = std::fabs(getCenter().y - rhs.getCenter().y);
	const auto ly = getLength().y / 2.0f + rhs.getLength().y / 2.0f;

	return (distx < lx && disty < ly);
}

template<typename T>
Box2d<T> Box2d<T>::getOverlapped(const Box2d<T>& rhs) const
{
	assert(hasIntersection(rhs));
	const auto minx = std::max(this->getStart().x, rhs.getStart().x);
	const auto miny = std::max(this->getStart().y, rhs.getStart().y);

	const auto maxx = std::min(this->getEnd().x, rhs.getEnd().x);
	const auto maxy = std::min(this->getEnd().y, rhs.getEnd().y);

	const Vector2df min_(minx, miny);
	const Vector2df max_(maxx, maxy);
	return Box2d(min_, max_);
}

template<typename T>
std::array< T, 8 > Box2d<T>::toArray() const
{
	return{
		getMinX(), getMaxY(),
		getMinX(), getMinY(),
		getMaxX(), getMinY(),
		getMaxX(), getMaxY()
	};
}

template class Box2d<float>;
template class Box2d<double>;