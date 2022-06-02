#include "SPHFlameParticle.h"

#include "../SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

SPHFlameParticle::SPHFlameParticle(const Vector3df& center, const float radius, SPHConstant* constant, SPHFlameConstant* flameConstant) :
	CSPHParticle(center, radius, constant),
	flameConstant(flameConstant),
	temperature(300.0f),
	fuel(0.0f),
	enthalpy(0.0f),
	dfuel(0.0f),
	isStatic(false)
{}

void SPHFlameParticle::init()
{
	CSPHParticle::init();
	enthalpy = 0.0f;
	dfuel = 1.0f;
}

void SPHFlameParticle::forwardTime(const float dt)
{
	if (isStatic) {
		return;
	}


	this->temperature += enthalpy * dt;
	this->fuel += dfuel * dt;

	if (isFire()) {
		const auto rs = this->getReactionSpeed();
		this->temperature += rs * dt;
		this->fuel -= rs * dt;
	}

	CSPHParticle::forwardTime(dt);
}

void SPHFlameParticle::solveHeatDiffuse(const SPHFlameParticle& rhs)
{
	const auto coe = (this->flameConstant->k_hd + rhs.flameConstant->k_hd) * 0.5f;
	const auto temperatureDiff = (rhs.temperature - this->temperature);
	const auto distance = Math::getDistance(getPosition(), rhs.getPosition());
	this->enthalpy += (coe * temperatureDiff * kernel->getViscosityKernelLaplacian(distance) * rhs.getVolume());
}

void SPHFlameParticle::solveFuelDiffuse(const SPHFlameParticle& rhs)
{
	const auto coe = (this->flameConstant->k_fd + rhs.flameConstant->k_fd) * 0.5f;
	const auto fuelDiff = (rhs.fuel - this->fuel);
	const auto distance = Math::getDistance(getPosition(), rhs.getPosition());
	this->dfuel += (coe * fuelDiff * kernel->getViscosityKernelLaplacian(distance) * rhs.getVolume());
}

float SPHFlameParticle::getReactionSpeed()
{
	return flameConstant->k_rs * temperature * fuel;
}

Vector3df SPHFlameParticle::getBuoyancyForce()
{
	const auto buo = (this->temperature - 300.0f) * this->flameConstant->k_buo * Vector3df(0,1,0);
	return buo;
}

bool SPHFlameParticle::isFire() const
{
	return this->temperature > 600.0f && this->fuel > 0.1f;
}
