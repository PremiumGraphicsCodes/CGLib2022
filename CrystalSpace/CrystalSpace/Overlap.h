#pragma once

namespace Crystal {
	namespace Math {
		class Plane3d;
		class Triangle3d;
		template<typename T>
		class Box3d;
		using Box3dd = Box3d<double>;
	}
	namespace Space {

class Overlap
{
public:
	static bool overlap(const Math::Box3dd& box, const Math::Plane3d& plane, const double tolerance);

	static bool overlap(const Math::Box3dd& box, const Math::Triangle3d& triangle);

};

	}
}