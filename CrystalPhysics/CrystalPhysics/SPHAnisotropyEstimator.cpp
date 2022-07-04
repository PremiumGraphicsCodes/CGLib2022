#include "SPHAnisotropyEstimator.h"

#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

using namespace Crystal::Space;
using namespace Crystal::Physics;

void SPHAnisotoropyEstimator::estimate(const std::vector<std::unique_ptr<SPHAnisotropicParticle>>& particles, const float searchRadius)
{
	const SPHKernel kernel(searchRadius);

	CompactSpaceHash3d spaceHash(searchRadius, particles.size());

	for (const auto& p : particles) {
		spaceHash.add(p.get());
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto& p = particles[i];
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		p->calculateDensity(neighbors, searchRadius, kernel);
	}
}
