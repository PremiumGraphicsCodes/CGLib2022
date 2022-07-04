#pragma once

#include <vector>
#include <memory>

#include "SurfaceConstruction/SPHSurfaceParticle.h"

namespace Crystal {
	namespace Physics {

		class SPHDensityEstimator
		{
		public:
			void estimate(const std::vector<std::unique_ptr<SPHSurfaceParticle>>& particles,const float searchRadius);

			//std::vector < Shape::Volume<double>* > getVolumes() { return volumes; }

		private:
		};
	}
}