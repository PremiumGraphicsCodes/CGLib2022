#include "DFSPHParticle.h"
#include "..\SPHConstant.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

float DFSPHParticle::getMass() const
{
	const auto diameter = radius * 2.0f;
	return constant->getDensity() * diameter * diameter * diameter;
}

void DFSPHParticle::calculateDensity()
{
	this->density = 0.0f;
	this->density += (kernel->getCubicSpline(0.0f) * this->getMass());
	for (auto n : neighbors) {
		const float distance = Math::getDistance(this->position, n->position);
		this->density += (kernel->getCubicSpline(distance) * n->getMass());
	}
}

void DFSPHParticle::calculateAlpha()
{
	this->alpha = 0.0;

	Vector3df a(0,0,0);
	float b = 0.0f;
	for (auto n : neighbors) {
		const auto v = this->position - n->position;
		const auto weight = (kernel->getCubicSplineGradient(v) * (float)n->getMass());
		a += weight;
		b += Math::getLengthSquared(weight);
	}

	this->alpha += Math::getLengthSquared(a) + b;

	if (this->alpha < 1.0e-6) {
		this->alpha = 0.0;
	}
}

void DFSPHParticle::calculateDpDt()
{
	this->dpdt = 0.0;
	for (auto n : neighbors) {
		const auto v = this->position - n->position;
		const auto grad = kernel->getCubicSplineGradient(v);
		dpdt += glm::dot(this->velocity, grad);
	}
	this->dpdt *= -density;
}

void DFSPHParticle::predictDensity(const float dt)
{
	calculateDpDt();
	predictedDensity = density + dt * dpdt;
}

void DFSPHParticle::calculateVelocityInDivergenceError(const float dt)
{
	const auto k_i = 1.0f / dt * dpdt * alpha;
	Vector3df dv(0,0,0);
	for (auto n : neighbors) {
		const auto k_j = 1.0f / dt * n->dpdt * n->alpha;
		const auto v = this->position - n->position;
		dv += n->getMass()* (k_i / density + k_j / n->density) * kernel->getCubicSplineGradient(v);
	}
	this->velocity -= dt * dv;
}

void DFSPHParticle::calculateVelocityInDensityError(const float dt)
{
	const auto k_i = (this->predictedDensity - constant->getDensity()) / dt / dt * alpha;
	Vector3df dv(0, 0, 0);
	for (auto n : neighbors) {
		const auto k_j = (n->predictedDensity - constant->getDensity()) / dt / dt * n->alpha;
		const auto v = this->position - n->position;
		dv += n->getMass() * (k_i / density + k_j / n->density) * kernel->getCubicSplineGradient(v);
	}
	this->velocity -= dt * dv;
}

void DFSPHParticle::calculateViscosity()
{
	for (auto n : neighbors) {
		const auto viscosityCoe = (this->constant->getViscosityCoe() + n->constant->getViscosityCoe()) * 0.5f;
		const auto velocityDiff = (n->velocity - this->velocity);
		const auto distance = Math::getDistance(position, n->position);
		this->force += viscosityCoe * velocityDiff * kernel->getCubicSpline(distance);

		/*
		const auto vel = n->getVelocity() - this->velocity;
		const auto weight = kernel->getViscosityKernelLaplacian(glm::length(v), kernel->getEffectLength());
		this->xvisc += vel * weight * 0.1f;
		*/
	}
}
