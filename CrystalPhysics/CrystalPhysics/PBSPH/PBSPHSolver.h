#pragma once

#include <vector>

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Box3d.h"
#include "CrystalScene/Scene/IAnimator.h"

namespace Crystal {
	namespace Physics {

class PBSPHParticle;
class PBFluidScene;

class PBSPHSolver : public Scene::IAnimator
{
public:
	PBSPHSolver();

	void step() override;

	void clear() { this->fluids.clear(); }

	void add(PBFluidScene* fluid) { this->fluids.push_back(fluid); }

	void simulate(const float dt, const int maxIter);

	void setBoundary(const Math::Box3dd& boundary) { this->boundary = boundary; }

	void setExternalForce(const Math::Vector3df& force) { this->externalForce = force; }

	//std::vector<PBSPHParticle*> getParticles() const { return particles; }

	void setTimeStep(const float dt) { this->maxTimeStep = dt; }

	//void setEffectLength(const float effectLength) { this->effectLength = effectLength; }

private:
	std::vector<PBFluidScene*> fluids;
	Math::Box3dd boundary;
	Math::Vector3df externalForce;
	float maxTimeStep;
	//float effectLength;

	float calculateTimeStep(const std::vector<PBSPHParticle*>& particles);
};

	}
}