#include "SPHFlameSolver.h"
#include "SPHFlameParticle.h"
#include "SPHFlameBoundarySolver.h"
#include "SPHFlameScene.h"

#include "../../../CrystalSpace/CrystalSpace/IndexedSortSearchAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void SPHFlameSolver::clear()
{
	//timeStep = 0.001;
}

void SPHFlameSolver::step()
{
	simulate(this->timeStep);
}

void SPHFlameSolver::simulate(const float timeStep)
{
	std::vector<SPHFlameParticle*> particles;

	for (auto fluid : flames) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	SPHKernel kernel(effectLength);
	for (auto p : particles) {
		p->setKernel(&kernel);
	}

	//kernel.setEffectLength(fluids.front()->)

	for (auto particle : particles) {
		particle->init();
	}

	IndexedSortSearchAlgo algo(effectLength);
	for (auto p : particles) {
		algo.add(p);
	}
	algo.createPairs();
	const auto& pairs = algo.getPairs();

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		auto p1 = static_cast<CSPHParticle*>(pairs[i].first);
		auto p2 = static_cast<CSPHParticle*>(pairs[i].second);
		p1->addDensity(*p2);
		p2->addDensity(*p1);
	}

	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		particles[i]->addSelfDensity();
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		auto p1 = static_cast<CSPHParticle*>(pairs[i].first);
		auto p2 = static_cast<CSPHParticle*>(pairs[i].second);
		p1->solvePressureForce(*p2);
		p2->solvePressureForce(*p1);
		p1->solveViscosityForce(*p2);
		p2->solveViscosityForce(*p1);
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		auto p1 = static_cast<SPHFlameParticle*>(pairs[i].first);
		auto p2 = static_cast<SPHFlameParticle*>(pairs[i].second);
		p1->solveHeatDiffuse(*p2);
		p2->solveHeatDiffuse(*p1);
		p1->solveFuelDiffuse(*p2);
		p2->solveFuelDiffuse(*p1);
	}

	for (auto p : particles) {
		p->addExternalForce(p->getBuoyancyForce());
		p->addExternalForce(externalForce);
	}


	SPHFlameBoundarySolver boundarySolver(timeStep, boundary);
	boundarySolver.solve(particles);

	for (auto p : particles) {
		p->forwardTime(timeStep);
	}

	for (auto fluid : flames) {
		fluid->getPresenter()->updateView();
	}
}