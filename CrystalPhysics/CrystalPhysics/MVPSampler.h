#pragma once

#include <list>

namespace Crystal {
	namespace Physics {
		class IMVPFluidScene;

class MVPSampler
{
public:
	void merge(const std::list<IMVPFluidScene*>& fluids, const double searchRadius);

	void split(const std::list<IMVPFluidScene*>& fluids);
};
	}
}