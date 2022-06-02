#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include <vector>
#include <optional>

namespace Crystal {
	namespace Math {
		template<typename T>
		class Line3d;
		using Line3dd = Line3d<double>;
		template<typename T>
		class Sphere3d;
		using Sphere3dd = Sphere3d<double>;
		class Ray3d;
		class Plane3d;
		class Triangle3d;
		class Quad3d;
		template<typename T>
		class Box3d;
		using Box3dd = Box3d<double>;
	}
	namespace Space {

struct Intersection
{
public:
	Intersection() :
		position(0,0,0),
		normal(0,0,1)
	{
	}

	Intersection(const Math::Vector3dd& position, const Math::Vector3dd& normal) :
		position(position),
		normal(normal)
	{}

	Math::Vector3dd position;
	Math::Vector3dd normal;
};

class IntersectionCalculator
{
public:
	bool calculateIntersection(const Math::Ray3d& ray, const Math::Sphere3dd& sphere, const double tolerance);

	bool calculateIntersection(const Math::Ray3d& ray, const Math::Plane3d& plane, const double tolerance);

	bool calculateIntersection(const Math::Ray3d& ray, const Math::Triangle3d& triangle, const double tolerance);

	static std::optional<Math::Vector3dd> calculateIntersectionParameters(const Math::Ray3d& ray, const Math::Triangle3d& triangle, const double tolerance);

	bool calculateIntersection(const Math::Ray3d& ray, const Math::Quad3d& quad, const double tolerance);

	bool calculateIntersection(const Math::Ray3d& ray, const Math::Box3dd& box, const double tolerance);

	bool calculateIntersection(const Math::Line3dd& line, const Math::Plane3d& plane, const double tolerance);

	bool calculateIntersection(const Math::Line3dd& line, const Math::Sphere3dd& sphere, const double tolerance);

	bool calculateIntersection(const Math::Line3dd& line, const Math::Triangle3d& triangle, const double tolerance);

	bool calculateIntersection(const Math::Line3dd& line, const Math::Quad3d& quad, const double tolerance);

	bool calculateIntersection(const Math::Triangle3d& lhs, const Math::Triangle3d& rhs, const double tolerance);

	std::vector<Intersection> getIntersections() const { return intersections; }

private:
	std::vector<Intersection> intersections;
};
	}
}