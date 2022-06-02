#pragma once

#include "Vector3d.h"
#include "ISurface3d.h"

namespace Crystal {
	namespace Math {

class Torus3d : public ISurface3dd
{
public:
	Torus3d();

	Torus3d(const Math::Vector3dd& center, const double R, const double r);

	Vector3dd getCenter() const { return center; }

	double getBigRadius() const { return R; }

	double getSmallRadius() const { return r; }

	Vector3dd getPosition(const double u, const double v) const override;

	Vector3dd getNormal(const double u, const double v) const override;

private:
	Vector3dd center;
	double R;
	double r;
};
	}
}