#pragma once

#include "ISurface3d.h"
#include "IVolume3d.h"
#include "Vector3d.h"

namespace Crystal {
	namespace Math {

class Cylinder3d : public ISurface3dd, public IVolume3dd
{
public:
	Cylinder3d();

	explicit Cylinder3d(const double radius);

	Cylinder3d(const double radius, const double height);

	Cylinder3d(const double radius, const double height, const Vector3dd& center);

	Vector3dd getPosition(const double u, const double v) const override;

	Vector3dd getPosition(const double r, const double h, const double w) const override;

	Vector3dd getNormal(const double u, const double v) const override;

	double getRadius() const { return radius; }

	double getHeight() const { return height; }

	Vector3dd getCenter() const { return center; }

	bool isInside(const Math::Vector3dd& position) const;

private:
	double radius;
	double height;
	Vector3dd center;
};
	}
}