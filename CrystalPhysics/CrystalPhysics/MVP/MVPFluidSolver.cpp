#include "MVPFluidSolver.h"

#include "MVPMassParticle.h"
#include "MVPVolumeParticle.h"

#include "MVPFluidScene.h"
#include "MVPFluidEmitterScene.h"

#include "../../../CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"
#include "../MVPSampler.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;

MVPFluidSolver::MVPFluidSolver() :
	externalForce(0.0, -9.8f, 0.0),
	buoyancy(0.0f, 0.0f, 0.0f)
{}

MVPFluidSolver::MVPFluidSolver(const int id) :
	IAnimator(id),
	externalForce(0.0, -9.8f, 0.0),
	buoyancy(0.0f, 0.0f, 0.0f)
{}

void MVPFluidSolver::setupBoundaries()
{
	this->boundarySolver.setup(effectLength);
}

void MVPFluidSolver::clear()
{
	fluids.clear();
	emitters.clear();
	maxTimeStep = 0.03f;
	boundarySolver.clear();
	currentTimeStep = 0;
}

void MVPFluidSolver::addFluidScene(MVPFluidScene* scene)
{
	this->fluids.push_back(scene);
}

void MVPFluidSolver::addEmitterScene(MVPFluidEmitterScene* scene)
{
	this->emitters.push_back(scene);
}

void MVPFluidSolver::addBoundary(CSGBoundaryScene* scene)
{
	this->boundarySolver.add(scene);
}

void MVPFluidSolver::addBoundaryScene(MVPFluidScene* scene)
{
	this->boundarySolver.addBoundaryScene(scene);
}

void MVPFluidSolver::step()
{
	simulate();
}

void MVPFluidSolver::simulate()
{
	std::vector<MVPVolumeParticle*> fluidParticles;
	std::list<IMVPFluidScene*> allFluids(this->fluids.begin(), this->fluids.end());

	for (auto emitter : emitters) {
		emitter->emitParticle(currentTimeStep);
		allFluids.push_back(emitter);
	}

	if (allFluids.empty()) {
		return;
	}

	if( currentTimeStep % 5 == 0 ) {
		MVPSampler sampler;
		sampler.merge(allFluids, effectLength);
	}

	for (auto fluid : allFluids) {
		const auto ps = fluid->getParticles();
		fluidParticles.insert(fluidParticles.end(), ps.begin(), ps.end());
	}

	for (auto particle : fluidParticles) {
		particle->reset(true);
	}

	if (fluidParticles.empty()) {
		currentTimeStep++;
		return;
	}

	const auto hashSize = fluidParticles.size();
	const auto searchRadius = effectLength;
	CompactSpaceHash3d spaceHash(searchRadius, static_cast<int>( hashSize));
	for (auto particle : fluidParticles) {
		spaceHash.add(particle);
	}

	//boundarySolver.setup(searchRadius);

#pragma omp parallel for
	for (int i = 0; i < fluidParticles.size(); ++i) {
		const auto particle = fluidParticles[i];
		const auto& neighbors = spaceHash.findNeighbors(particle);
		for (auto n : neighbors) {
			particle->addNeighbor(static_cast<MVPVolumeParticle*>(n));
		}
		const auto staticNeighbors = boundarySolver.findNeighbors(particle->getPositionf());
		for (auto n : staticNeighbors) {
			particle->addNeighbor(static_cast<MVPVolumeParticle*>(n));
		}
	}

	for(auto particle : fluidParticles) {
		boundarySolver.createGphosts(particle);
	}

	double time = 0.0;
	while (time < maxTimeStep) {
		const auto dt = calculateTimeStep(fluidParticles);

		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			particle->updateMassPositions();
			particle->updateMassVelocities();
			particle->updateMassTemperatures();
		}

#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			particle->updateInnerPoints();
			particle->calculateDensity();
			particle->calculateViscosityForce();
			particle->calculateHeatDiffuse();
		}
		

#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			//boundarySolver.createMacro(particle);
			boundarySolver.solvePressure(particle, dt);
		}

		for (auto particle : fluidParticles) {
			const auto buo = buoyancy * (particle->getTemperature() - 300.0f) *  particle->getDensity();
			particle->addForce(buo);
			particle->addForce(externalForce * particle->getDensity());
			particle->calculateDragForce();
			particle->calculateDragHeat();
			//particle->stepTime(dt);
		}

		// solve incompressibility.
		float relaxationCoe = 1.0f;
		for (int i = 0; i < 2; ++i) {
			for (auto particle : fluidParticles) {
//				particle->reset(false);
				particle->updateMassPositions();
			}

#pragma omp parallel for
			for (int i = 0; i < fluidParticles.size(); ++i) {
				const auto particle = fluidParticles[i];
				particle->updateInnerPoints();
				//particle->calculateDensity();
				particle->calculatePressureForce(relaxationCoe, dt);
			}
			relaxationCoe *= 0.85f;


			//for (auto particle : fluidParticles) {
			//	solveBoundary(particle, dt);
			//}
			//	solveBoundary(particles);
		}

		for (auto particle : fluidParticles) {
			particle->stepTime(dt);
		}

		time += dt;
	}

	auto densityError = 0.0;
	for (auto particle : fluidParticles) {
		densityError += particle->getDensity() / (double)fluidParticles.size();
	}
	std::cout << densityError << std::endl;

	auto aveTemperature = 0.0;
	for (auto p : fluidParticles) {
		aveTemperature += p->getTemperature() / (double)fluidParticles.size();
	}
	std::cout << aveTemperature << std::endl;

	boundarySolver.clearGphosts();

	MVPSampler sampler;
	if (currentTimeStep % 2 == 0) {
		sampler.split(allFluids);
	}

	currentTimeStep++;
}

float MVPFluidSolver::calculateTimeStep(const std::vector<MVPVolumeParticle*>& particles)
{
	float maxVelocity = 0.0f;
	for (auto p : particles) {
		maxVelocity = std::max<float>(maxVelocity, Math::getLengthSquared( p->getVelocity() ) );
	}
	if (maxVelocity < 1.0e-3) {
		return maxTimeStep;
	}
	maxVelocity = std::sqrt(maxVelocity);
	const auto dt = 0.4f * particles.front()->getRadius() * 2.0f / maxVelocity;
	return maxTimeStep;
	//return std::min(dt, maxTimeStep);
}


void MVPUpdater::step()
{
	for (auto fluid : fluids) {
		fluid->getPresenter()->updateView();
		//for(auto b : fluid->get)
	}
	//for(auto b : csgB)
}
