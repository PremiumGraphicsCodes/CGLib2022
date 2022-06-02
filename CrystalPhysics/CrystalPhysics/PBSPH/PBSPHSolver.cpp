#include "PBSPHSolver.h"
#include "PBFluidScene.h"
#include "PBSPHParticle.h"

#include "PBSPHBoundarySolver.h"

#include "../../../CrystalSpace/CrystalSpace/IndexedSortSearchAlgo.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

PBSPHSolver::PBSPHSolver() :
	maxTimeStep(0.01f)
{}

void PBSPHSolver::step()
{
	simulate(maxTimeStep, 3);
}

void PBSPHSolver::simulate(const float maxTimeStep, const int maxIter)
{
	std::vector<PBSPHParticle*> particles;
	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	for (auto p : particles) {
		p->init();
	}

	const auto dt = maxTimeStep;//calculateTimeStep(particles);

	PBSPHBoundarySolver boundarySolver(boundary);
	for (auto p : particles) {
		p->addExternalForce(externalForce);
		p->predictPosition_(dt);
	}

	const auto searchLength = fluids.front()->getKernel()->getEffectLength() * 1.1f;
	IndexedSortSearchAlgo finder(searchLength);
	for (auto p : particles) {
		finder.add(p);
	}
	finder.createPairs();

	const auto& pairs = finder.getPairs();


	for (int iter = 0; iter < maxIter; ++iter) {
		for (int i = 0; i < particles.size(); ++i) {
			const auto p = static_cast<PBSPHParticle*>(particles[i]);
			p->setDensity(0.0f);
			p->dx = Math::Vector3df(0, 0, 0);
		}

		boundarySolver.addDX(particles, dt);

		for (int i = 0; i < particles.size(); ++i) {
			const auto p = static_cast<PBSPHParticle*>(particles[i]);
			p->addSelfDensity();
		}

#pragma omp parallel for
		for (int i = 0; i < pairs.size(); ++i) {
			const auto p1 = static_cast<PBSPHParticle*>(pairs[i].first);
			const auto p2 = static_cast<PBSPHParticle*>(pairs[i].second);
			p1->addDensity(*p2);
			p2->addDensity(*p1);
		}

#pragma omp parallel for
		for (int i = 0; i < pairs.size(); ++i) {
			const auto p1 = static_cast<PBSPHParticle*>(pairs[i].first);
			const auto p2 = static_cast<PBSPHParticle*>(pairs[i].second);
			p1->calculatePressure(*p2);
			p2->calculatePressure(*p1);
		}

		boundarySolver.calculatePressure(particles);

		for (int i = 0; i < particles.size(); ++i) {
			const auto p = particles[i];
			p->updatePredictPosition();
		}
	}

	for (int i = 0; i < particles.size(); ++i) {
		particles[i]->xvisc = Vector3df(0, 0, 0);
	}
	//boundarySolver.calculateViscosity(particles);
	for (int i = 0; i < pairs.size(); ++i) {
		const auto p1 = static_cast<PBSPHParticle*>(pairs[i].first);
		const auto p2 = static_cast<PBSPHParticle*>(pairs[i].second);
		p1->calculateViscosity(*p2);
		p2->calculateViscosity(*p1);
	}

	for (auto p : particles) {
		p->updateVelocity(dt);
		p->addVelocity(p->xvisc);
		p->updatePosition();
		//	p->integrate(dt);
	}

	auto densityError = 0.0;
	for (auto particle : particles) {
		densityError += particle->getDensity() / (double)particles.size();
	}
	std::cout << densityError << std::endl;


	for (auto fluid : fluids) {
		fluid->getPresenter()->updateView();
	}
}

float PBSPHSolver::calculateTimeStep(const std::vector<PBSPHParticle*>& particles)
{
	float maxVelocity = 0.0f;
	for (auto p : particles) {
		maxVelocity = std::max<float>(maxVelocity, Math::getLengthSquared(p->getVelocity()));
	}
	if (maxVelocity < 1.0e-3) {
		return maxTimeStep;
	}
	maxVelocity = std::sqrt(maxVelocity);
	const auto dt = 0.4f * particles.front()->getRadius() * 2.0f / maxVelocity;
	return maxTimeStep;
	//return std::min(dt, maxTimeStep);
}