#include "PBSPHBoundaryParticle.h"
#include "PBFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

PBSPHBoundaryParticle::PBSPHBoundaryParticle(const Vector3df& center, const float radius, PBFluidScene* scene) :
	position(center),
	radius(radius),
	//	ISPHParticle(center, radius),
	scene(scene)
{
	this->density = scene->getRestDensity();
}

void PBSPHBoundaryParticle::init()
{
	density = 0.0;
}

float PBSPHBoundaryParticle::getDensityRatio() const
{
	return density / scene->getRestDensity();
}

float PBSPHBoundaryParticle::getMass() const
{
	const auto diameter = radius * 2.0f;
	return scene->getRestDensity() * diameter * diameter * diameter;
}

float PBSPHBoundaryParticle::getVolume() const
{
	return getMass() / density;
}

float PBSPHBoundaryParticle::getRestVolume() const
{
	return getMass() / scene->getRestDensity();
}

void PBSPHBoundaryParticle::setDefaultDensity()
{
	this->density = scene->getRestDensity();
}

void PBSPHBoundaryParticle::calculatePressure(const PBSPHParticle& rhs)
{
	/*
	const auto v = this->getPredictPosition() - rhs.getPredictPosition();
	const auto weight = getKernel()->getPoly6KernelGradient(v);
	const auto c = this->getConstraint() + rhs.getConstraint();
	dx += c * weight / scene->getRestDensity() * scene->getStiffness();//0.05f;
	*/
}

void PBSPHBoundaryParticle::calculateViscosity(const PBSPHParticle& rhs)
{
	/*
	const auto v = this->getPredictPosition() - rhs.getPredictPosition();
	const auto vel = rhs.getVelocity() - this->velocity;
	const auto weight = getKernel()->getViscosityKernelLaplacian(glm::length(v));
	this->xvisc += vel * weight * scene->getViscosity();
	*/
}