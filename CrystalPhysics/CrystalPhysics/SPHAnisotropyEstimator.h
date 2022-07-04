#pragma once

#include <vector>
#include <memory>

#include "SurfaceConstruction/SPHAnisotropicParticle.h"

namespace Crystal {
	namespace Physics {

class SPHAnisotoropyEstimator
{
public:
	void add(const Math::Vector3df& position, const float particleRadius);

	void estimateIsotoropy(const float searchRadius);

	//std::vector < Shape::Volume<double>* > getVolumes() { return volumes; }

private:
	std::vector<std::unique_ptr<SPHAnisotropicParticle>> particles;

};
	}
}