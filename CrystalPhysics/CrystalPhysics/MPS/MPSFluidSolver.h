#pragma once

#include "MPSParticle.h"
#include <list>
#include "CrystalScene/Scene/IAnimator.h"

namespace Crystal {
	namespace Physics {
		class MPSFluidScene;

class MPSFluidSolver : public Scene::IAnimator
{
public:
	void step() override;

	void setEffectLength(const float effectRadius) { this->effectRadius = effectRadius; }

	void addFluid(MPSFluidScene* fluid) { this->fluids.push_back(fluid); }

	Math::Vector3df calculatePressureGradient(const MPSParticle* lhs, const MPSParticle* rhs, const float maxRadius);


private:
	std::list<MPSFluidScene*> fluids;
	Math::Vector3df externalForce;
	float effectRadius;
	float timeStep;
};
	}
}