#pragma once

#include "Crystal/Math/Box3d.h"
#include "CrystalScene/Scene/IAnimator.h"

#include "../SPHKernel.h"
//#include "ISPHSolver.h"
#include <vector>

namespace Crystal {
	namespace Physics {
		class SPHFlameScene;

class SPHFlameSolver : public Scene::IAnimator
{
public:
	SPHFlameSolver() : timeStep(0.001f)
	{}

	void add(SPHFlameScene* flame) { this->flames.push_back(flame); }

	void clear();

	void step() override;

	void simulate(const float timeStep);

	void setTimeStep(const float timeStep) { this->timeStep = timeStep; }

	//int getTimeStep() const { return timeStep; }

	void setExternalForce(const Math::Vector3df& force) { this->externalForce = force; }

	//std::vector<CSPHParticle*> getParticles() const { return particles; }

	void setBoundary(const Math::Box3dd& boundary) { this->boundary = boundary; }

	void setEffectLenth(const float length) { this->effectLength = length; }

private:
	float timeStep;
	float effectLength = 1.25f;
	//SPHKernel kernel;
	std::vector<SPHFlameScene*> flames;
	Math::Vector3df externalForce;
	Math::Box3dd boundary;
};

	}
}