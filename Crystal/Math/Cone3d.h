#pragma once

#include "ISurface3d.h"
#include "IVolume3d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Cone3d : public ISurface3dd, public IVolume3dd
{
public:
	Cone3d();

	Cone3d(const Vector3dd& bottom, const double radius, const double height);

	Vector3dd getPosition(const double u, const double v) const override;

	Vector3dd getPosition(const double u, const double v, const double w) const override;

	Vector3dd getNormal(const double u, const double v) const override;

	Vector3dd getBottom() const { return bottom; }

	double getRadius() const { return radius; }

	double getHeight() const { return height; }

	bool isInside(const Math::Vector3dd& position) const override;

private:
	Vector3dd bottom;
	double radius;
	double height;
};
	}
}