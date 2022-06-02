#include "CSPHParticle.h"
#include "../SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

CSPHParticle::CSPHParticle(const Vector3df& position, const float radius, SPHConstant* constant) :
	position(position),
	radius(radius),
	constant(constant)
{
	density = (constant->getDensity());
}

void CSPHParticle::init()
{
	density = 0.0;
	normal = Math::Vector3df(0.0f, 0.0f, 0.0f);
	force = Math::Vector3df(0.0f, 0.0f, 0.0f);
}

float CSPHParticle::getDensityRatio() const
{
	return density / constant->getDensity();
}

float CSPHParticle::getPressure() const
{
	return constant->getPressureCoe() * (std::pow(getDensityRatio(), 1.0f) - 1.0f);
}

float CSPHParticle::getMass() const
{
	return constant->getDensity() * std::pow(getDiameter(), 3.0f);
}

float CSPHParticle::getVolume() const
{
	return getMass() / density;
}

float CSPHParticle::getRestVolume() const
{
	return getMass() / constant->getDensity();
}

void CSPHParticle::forwardTime(const float timeStep)
{
	const auto& acc = getAccelaration() / getDensity();
	this->velocity += (acc * timeStep);
	this->position += (velocity * timeStep);
}

void CSPHParticle::addExternalForce(const Vector3df& externalForce)
{
	this->force += externalForce * getDensity();
}

void CSPHParticle::solveNormal(const CSPHParticle& rhs)
{
	const auto& distanceVector = this->getPosition() - rhs.getPosition();
	this->normal += kernel->getPoly6KernelGradient(distanceVector) * rhs.getVolume();
	//pairs[i].getParticle1()->addForce(viscosityCoe * velocityDiff * kernel.getViscosityKernelLaplacian(distance, effectLength) * pairs[i].getParticle2()->getVolume());
}

void CSPHParticle::solveSurfaceTension(const CSPHParticle& rhs)
{
	if (getLengthSquared(this->normal) < 0.1f) {
		return;
	}
	const auto distance = Math::getDistance(this->position, rhs.position);
	const auto n = glm::normalize(this->normal);
	const float tensionCoe = (this->constant->getTensionCoe() + rhs.constant->getTensionCoe()) * 0.5f;;
	this->force -= tensionCoe * kernel->getPoly6KernelLaplacian(distance) * n;
}

void CSPHParticle::solvePressureForce(const CSPHParticle& rhs)
{
	const auto pressure = (this->getPressure() + rhs.getPressure()) * 0.5f;
	const auto& distanceVector = (this->getPosition() - rhs.getPosition());
	const auto& f = kernel->getSpikyKernelGradient(distanceVector) * pressure * rhs.getVolume();
	this->force += f;
}

void CSPHParticle::solveViscosityForce(const CSPHParticle& rhs)
{
	const auto viscosityCoe = (this->constant->getViscosityCoe() + rhs.constant->getViscosityCoe()) * 0.5f;
	const auto& velocityDiff = (rhs.velocity - this->velocity);
	const auto distance = Math::getDistance(this->position, rhs.position);
	this->addForce(viscosityCoe * velocityDiff * kernel->getViscosityKernelLaplacian(distance) * rhs.getVolume());
}

void CSPHParticle::addSelfDensity()
{
	this->addDensity(kernel->getPoly6Kernel(0.0) * this->getMass());
}

void CSPHParticle::addDensity(const CSPHParticle& rhs)
{
	const float distance = Math::getDistance(this->position, rhs.position);
	this->addDensity(kernel->getPoly6Kernel(distance) * rhs.getMass());
}

void CSPHParticle::move(const Vector3df& v)
{
	this->position += v;
}