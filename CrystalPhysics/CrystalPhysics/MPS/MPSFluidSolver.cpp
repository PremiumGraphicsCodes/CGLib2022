#include "MPSFluidSolver.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "MPSFluidScene.h"

#include <vector>

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

namespace {
	constexpr int DIM = 3;
}

void MPSFluidSolver::step()
{
	std::vector<MPSParticle*> particles;
	
	for (auto fluid : this->fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	CompactSpaceHash3d spaceHash(effectRadius, static_cast<int>(particles.size()));
	for (auto p : particles) {
		spaceHash.add(p);
	}

	for (auto p : particles) {
		const auto neighbors = spaceHash.findNeighbors(p);
		for (auto n : neighbors) {
			p->addNeighbor(static_cast<MPSParticle*>(n));
		}
	}

	// calculate number density.
	for (auto p : particles) {
		p->calculateNumberDensity(effectRadius);
	}

	for (auto p : particles) {
		p->addExternalForce(this->externalForce);
		p->calculateViscosity(effectRadius);
	}

	// add viscosity force.

	for (auto p : particles) {
		p->forwardTime(timeStep);
	}
}