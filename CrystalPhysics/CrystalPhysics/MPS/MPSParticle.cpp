#include "MPSParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	constexpr int DIM = 2;
}

MPSParticle::MPSParticle(const Vector3df& position) :
	position(position),
	pressure(0.0f),
	force(Vector3df(0,0,0)),
	//radius(radius),
	acc(0.0),
	numberDensity(0.0f)
{}

void MPSParticle::forwardTime(const float timeStep)
{
	//const auto& acc = getAccelaration() / getDensity();
	this->velocity += (acc * timeStep);
	this->position += (velocity * timeStep);
}

void MPSParticle::calculateNumberDensity(const float maxRadius)
{
	for (auto n : neighbors) {
		this->numberDensity += this->calculateNumberDensity(n, maxRadius);
	}
}

void MPSParticle::calculatePressureGradient(const float maxRadius)
{
	for (auto n : neighbors) {
		this->force += this->calculatePressureGradient(n, maxRadius);
	}
}

void MPSParticle::calculateViscosity(const float maxRadius)
{
	for (auto n : neighbors) {
		this->force += this->calculateViscosity(n, maxRadius);
	}
}

void MPSParticle::calculateN0(const float maxRadius)
{
	calculateNumberDensity(maxRadius);
	this->n0 = this->getNumberDensity();
}

void MPSParticle::calculateLamda0(const float maxRadius)
{
	float v = 0.0f;
	for (auto n : neighbors) {
		const auto d2 = getDistanceSquared(this->getPositionf(), n->getPositionf());
		v += d2 * this->calculateWeight(std::sqrt(d2), maxRadius);
	}
	this->lamda0 = v / this->n0;
}

float MPSParticle::calculateNumberDensity(const MPSParticle* rhs, const float maxRadius)
{
	const float distance = getDistance(this->getPositionf(), rhs->getPositionf());
	const float weight = calculateWeight(distance, maxRadius);
	return weight;
}

Vector3df MPSParticle::calculatePressureGradient(const MPSParticle* rhs, const float maxRadius)
{
	const float coe = DIM / this->getN0();
	const float distanceSquared = getDistanceSquared(this->getPositionf(), rhs->getPositionf());
	const auto vector = rhs->getPositionf() - this->getPositionf();
	const float pressureDiff = rhs->getPressure() - this->getPressure();
	const float weight = calculateWeight(std::sqrt(distanceSquared), maxRadius);
	return coe * pressureDiff / distanceSquared * vector * weight;
}

Vector3df MPSParticle::calculateViscosity(const MPSParticle* rhs, const float maxRadius)
{
	const float coe = 2.0f * DIM / (this->getN0() * this->getLamda0());
	const float distance = getDistance(this->getPositionf(), rhs->getPositionf());
	const auto velocityDiff = rhs->getVelocity() - this->getVelocity();
	const float weight = calculateWeight(distance, maxRadius);
	return coe * velocityDiff * weight;
}

float MPSParticle::calculateWeight(const float r, const float maxRadius)
{
	if (r > maxRadius) {
		return 0.0f;
	}
	return (maxRadius / r) - 1.0f;
}
