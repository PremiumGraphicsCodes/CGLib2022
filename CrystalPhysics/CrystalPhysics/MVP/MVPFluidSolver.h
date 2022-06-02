#pragma once

#include <vector>
#include <list>

#include "CrystalScene/Scene/IScene.h"
#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Box3d.h"
#include "Crystal/Shape/IParticle.h"
#include "CrystalScene/Scene/IAnimator.h"
#include "Crystal/Math/Triangle3d.h"

#include "MVPBoundarySolver.h"

namespace Crystal {
	namespace Physics {
		class MVPVolumeParticle;
		class MVPFluidScene;
		class MVPFluidEmitterScene;
		class IMVPFluidScene;
		class CSGBoundaryScene;

class MVPFluidSolver : public Scene::IAnimator
{
public:
	MVPFluidSolver();

	explicit MVPFluidSolver(const int id);

	void setupBoundaries();

	void clear();

	void addFluidScene(MVPFluidScene* scene);

	void addBoundaryScene(MVPFluidScene* scene);

	void addEmitterScene(MVPFluidEmitterScene* scene);

	void addBoundary(CSGBoundaryScene* scene);

	void setMaxTimeStep(const float maxTimeStep) { this->maxTimeStep = maxTimeStep; }

	void setEffectLength(const float effectLength) { this->effectLength = effectLength; }

	void setExternalForce(const Math::Vector3df& externalForce) { this->externalForce = externalForce; }

	void setBuoyancy(const Math::Vector3df& buoyancy) { this->buoyancy = buoyancy; }

	void simulate();

	void step() override;

	int getTimeStep() const { return currentTimeStep;}

	std::list<MVPFluidScene*> getFluids() const { return fluids; }

	std::list<MVPFluidEmitterScene*> getEmitters() const { return emitters; }

	//std::vector<Math::Triangle3d> getTriangles() const { return triangles; }

private:

	float calculateTimeStep(const std::vector<MVPVolumeParticle*>& particles);
	
	std::list<MVPFluidScene*> fluids;
	std::list<MVPFluidEmitterScene*> emitters;
	//std::list<MVPMassParticle*> tinyParticles;
	MVPBoundarySolver boundarySolver;
	float effectLength = 2.0f;
	float maxTimeStep = 0.03f;
	int currentTimeStep = 0;
	Math::Vector3df externalForce;
	Math::Vector3df buoyancy;
};

class MVPUpdater : public Scene::IAnimator
{
public:
	MVPUpdater() {}

	void add(Scene::IScene* f) { fluids.push_back(f); }

	void step() override;

private:
	std::list<Scene::IScene*> fluids;
};


	}
}