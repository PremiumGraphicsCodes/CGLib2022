#include "Solid.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

Solid::Solid(std::unique_ptr<IVolume3dd> shape) :
	shape(std::move(shape)),
	matrix(Math::Identity<double>())
{}

Box3dd Solid::getBoundingBox() const
{
	const auto p1 = shape->getPosition(0, 0, 0);
	const auto p2 = shape->getPosition(1, 1, 1);
	return Math::Box3d(p1,p2);
}