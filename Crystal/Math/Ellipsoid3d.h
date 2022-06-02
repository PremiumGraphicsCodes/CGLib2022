#pragma once

#include "Vector3d.h"
#include "IVolume3d.h"
#include "ISurface3d.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Box3d;

class Ellipsoid3d : public ISurface3dd
{
public:
	Ellipsoid3d();

	Ellipsoid3d(const Vector3dd& center, const Vector3dd& uvec, const Vector3dd& vvec, const Vector3dd& wvec);

	Vector3dd getPosition(const double u, const double v) const override;

	Vector3dd getNormal(const double u, const double v) const override;

	Vector3dd getCenter() const { return center; }

	Vector3dd getUVec() const { return uvec; }

	Vector3dd getVVec() const { return vvec; }

	Vector3dd getWVec() const { return wvec; }

	bool isSame(const Ellipsoid3d& rhs, const double tolerance) const;

	void moveTo(const Vector3dd& pos) { this->center = pos; }

	Box3d<double> getBoundingBox() const;

private:
	Vector3dd center;
	Vector3dd uvec;
	Vector3dd vvec;
	Vector3dd wvec;
};

	}
}
