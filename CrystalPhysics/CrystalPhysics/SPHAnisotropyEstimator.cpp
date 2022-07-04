#include "SPHAnisotropyEstimator.h"

#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"

#include "SurfaceConstruction/WPCA.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void SPHAnisotoropyEstimator::add(const Vector3df& position, const float particleRadius)
{
	particles.push_back(new SPHAnisotropicParticle(position, particleRadius));
}

void SPHAnisotoropyEstimator::estimateIsotoropy(const float searchRadius)
{
	const SPHKernel kernel(searchRadius);

	CompactSpaceHash3d spaceHash(searchRadius, particles.size());

	for (auto p : particles) {
		spaceHash.add(p);
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto& p = particles[i];
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		p->calculateDensity(neighbors, searchRadius, kernel);
	}
}

void SPHAnisotoropyEstimator::estimateAnIsotoropy(const float searchRadius)
{
	const SPHKernel kernel(searchRadius);

	CompactSpaceHash3d spaceHash(searchRadius, particles.size());

	for (auto p : particles) {
		spaceHash.add(p);
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto& p = particles[i];
		const auto neighbors = spaceHash.findNeighbors(p->getPosition());
		p->calculateDensity(neighbors, searchRadius, kernel);
		WPCA wpca;
		wpca.setup(p, neighbors, searchRadius);
		const auto wm = wpca.calculateWeightedMean(p, neighbors, searchRadius);
		p->correctedPosition(0.95, wm);
		p->calculateAnisotoropicMatrix(neighbors, searchRadius);
	}
}
