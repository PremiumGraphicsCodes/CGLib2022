#pragma once

#include <vector>
#include <memory>

#include "SurfaceConstruction/SPHAnisotropicParticle.h"

namespace Crystal {
	namespace Physics {

class SPHAnisotoropyEstimator
{
public:
	void estimate(const std::vector<std::unique_ptr<SPHAnisotropicParticle>>& particles,const float searchRadius);

	//std::vector < Shape::Volume<double>* > getVolumes() { return volumes; }

private:
};
	}
}