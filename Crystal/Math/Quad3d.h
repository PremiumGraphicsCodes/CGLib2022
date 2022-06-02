#pragma once

#include "Vector3d.h"
#include "ISurface3d.h"
#include "Plane3d.h"

namespace Crystal {
	namespace Math {
		class Plane3d;

class Quad3d : public ISurface3dd
{
public:
	Quad3d();

	Quad3d(const Vector3dd& origin, const Vector3dd& uvec, const Vector3dd& vvec);

	Vector3dd getPosition(const double u, const double v) const override;

	Vector3dd getNormal(const double u, const double v) const;

	Vector3dd getNormal() const;

	bool isInside(const Vector3dd& p) const;

	Vector3dd getV0() const { return origin; }

	Vector3dd getV1() const { return origin + uvec; }

	Vector3dd getV2() const { return origin + uvec + vvec; }

	Vector3dd getV3() const { return origin + vvec; }

	Plane3d toPlane() const;

	bool isSame(const Quad3d& rhs, const double tolerance) const;

private:
	Vector3dd origin;
	Vector3dd uvec;
	Vector3dd vvec;
};
	}
}