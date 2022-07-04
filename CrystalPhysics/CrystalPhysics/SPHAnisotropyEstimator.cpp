#include "SPHAnisotropyEstimator.h"

#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void SPHAnisotoropyEstimator::add(const Vector3df& position, const float particleRadius)
{
	particles.push_back(std::make_unique<SPHAnisotropicParticle>(position, particleRadius));
}

void SPHAnisotoropyEstimator::estimateIsotoropy(const float searchRadius)
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
