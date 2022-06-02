#pragma once

#include <array>
#include "Vector3d.h"
#include "Matrix3d.h"
#include "Matrix4d.h"

namespace Crystal {
	namespace Math {
		class Plane3d;
		template<typename T>
		class Box3d;

class Triangle3d
{
public:
	Triangle3d();

	explicit Triangle3d(const std::array<Vector3dd, 3>& vertices);

	Triangle3d(const Vector3dd& v1, const Vector3dd& v2, const Vector3dd& v3);

	Vector3dd getNormal() const;

	double getArea() const;

	bool isInside(const Vector3dd& p) const;

	Plane3d toPlane() const;

	std::array<Vector3dd, 3> getVertices() const { return vertices; }

	Vector3dd getV0() const { return vertices[0]; }

	Vector3dd getV1() const { return vertices[1]; }

	Vector3dd getV2() const { return vertices[2]; }

	void translate(const Math::Vector3dd& v);

	void transform(const Math::Matrix3dd& matrix);

	void transform(const Math::Matrix4dd& matrix);

	Box3d<double> getBoundingBox() const;

	bool isSame(const Triangle3d& rhs, const double tolerance) const;

private:
	std::array<Vector3dd, 3> vertices;
};

	}
}