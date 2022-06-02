#pragma once

#include "Crystal/Shape/Volume.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"

namespace Crystal {
	namespace Space {

class VolumeConvertAlgo
{
public:
	VolumeConvertAlgo(const Math::Box3dd& box, const std::array<size_t,3>& resolutions);

	void add(Shape::IParticle* particle);

	void build(const double searchRadius);

private:
	Shape::Volume<double> volume;
	std::list<Shape::IParticle*> particles;
};
	}
}