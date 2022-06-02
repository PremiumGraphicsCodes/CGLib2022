#pragma once

#include "Vector2d.h"
#include "Matrix2d.h"
#include "Matrix3d.h"

namespace Crystal {
	namespace Math {

class Line2dd
{
public:
	Line2dd();

	Line2dd(const Math::Vector2dd& origin, const Math::Vector2dd& dir);

	static Line2dd fromPoints(const Vector2dd& start, const Vector2dd& end)
	{
		return Line2dd(start, end - start);
	}

	Math::Vector2dd getStart() const { return origin; }

	Math::Vector2dd getEnd() const { return origin + dir; }

	Math::Vector2dd getDirection() const { return dir; }

	double getLength() const { return glm::distance(origin, dir); }

	void move(const Math::Vector2dd& v) { this->origin += v; }

	void transform(const Math::Matrix2dd& m) { dir = m * dir; }

	void transform(const Math::Matrix3dd& m) { dir = m * glm::vec3(dir, 1.0); }

private:
	Math::Vector2dd origin;
	Math::Vector2dd dir;
};
	}
}