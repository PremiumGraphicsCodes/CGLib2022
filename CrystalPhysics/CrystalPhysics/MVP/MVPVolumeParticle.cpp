#include "MVPVolumeParticle.h"

#include "MVPFluidScene.h"

#include "../SPHKernel.h"

#include "Crystal/Math/Gaussian1d.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPVolumeParticle::MVPVolumeParticle(const float radius, const Vector3dd& position) :
	radius(radius),
	position(position),
	restMass(0.0f),
	temperature(300.0f),
	enthaply(0.0)
{}

MVPVolumeParticle::~MVPVolumeParticle()
{
	for (auto p : massParticles) {
		delete p;
	}
	//points.clear();
}

void MVPVolumeParticle::setPressureCoe(const float c)
{
	this->pressureCoe = c;
	for (auto p : massParticles) {
		p->setPressureCoe(c);
	}
}

void MVPVolumeParticle::setViscosityCoe(const float c)
{
	this->viscosityCoe = c;
	for (auto p : massParticles) {
		p->setViscosityCoe(c);
	}
}

void MVPVolumeParticle::setHeatDiffuseCue(const float c)
{
	for (auto p : massParticles) {
		p->setHeatDiffuseCoe(c);
	}
}

void MVPVolumeParticle::reset(bool resetMicro)
{
	this->force = Math::Vector3df(0, 0, 0);
	this->enthaply = 0.0;
	this->averagedCenter = this->position;
	//this->dv = Math::Vector3df(0, 0, 0);
	if (resetMicro) {
		this->neighbors.clear();
		this->neighbors.reserve(64);
	}
}

void MVPVolumeParticle::calculateDensity()
{
	float mass = 0.0f;
	for (auto m : innerPoints) {
		mass += m->getMass();
	}
	this->density = (mass / restMass);
	/*
	for (auto m : innerPoints) {
		const auto p = (this->density - 1.0) * this->pressureCoe;
		m->setPressureCoe(p);
	}
	*/
}

void MVPVolumeParticle::calculatePressureForce(const float relaxationCoe, const float dt)
{
	Math::Vector3df averagedCenter(0, 0, 0);
	for (auto mp : innerPoints) {
		averagedCenter += (mp->position) / static_cast<float>(innerPoints.size());// mp->getPressureCoe();
	}
	this->averagedCenter = averagedCenter;
}

void MVPVolumeParticle::calculateViscosityForce()
{
	Math::Vector3df f(0, 0, 0);
	for (auto mp : innerPoints) {
		f -= ( this->velocity - mp->getVelocity()) * mp->getMass() * mp->getViscosityCoe();
	}
	this->force += f;
}

#include <iostream>

void MVPVolumeParticle::calculateHeatDiffuse()
{
	float t = 0.0;
	for (auto mp : innerPoints) {
		t -= (this->temperature - mp->getTemperature()) * mp->getMass() * mp->getHeatDiffuseCoe();
	}
	this->enthaply += t / (float)innerPoints.size();
}

/*
void MVPVolumeParticle::calculateVorticity()
{
	vorticity = Vector3df(0, 0, 0);
	for (auto mp : innerPoints) {
		const auto p = (mp->position - this->position);
		const auto v = (mp->getVelocity() - this->velocity);
		vorticity += glm::cross(p, v) * this->vorticityCoe;
	}
}
*/

void MVPVolumeParticle::stepTime(const float dt)
{
	const auto dv = this->position - averagedCenter;
	this->force += dv /*/ dt / dt*/ * this->density * this->pressureCoe;


	const auto acc = (force) / getDensity();
	this->velocity += acc * dt;
	this->position += this->velocity * dt;

	this->temperature += this->enthaply * dt;

	for (auto c : this->massParticles) {
		c->lifeTime++;
	}
}

float MVPVolumeParticle::getDensity() const
{
	return this->density;
}

void MVPVolumeParticle::updateMassPositions()
{
	for (auto mp : this->massParticles) {
		mp->updatePosition(this->averagedCenter);
	}
}

void MVPVolumeParticle::updateMassVelocities()
{
	for (auto mp : this->massParticles) {
		mp->updateVelocity(this->velocity);
	}
}

void MVPVolumeParticle::updateMassTemperatures()
{
	for (auto mp : this->massParticles) {
		mp->updateTemperature(this->temperature);
	}
}

void MVPVolumeParticle::updateInnerPoints()
{
	const auto p = this->averagedCenter;
	const auto r = this->radius;
	innerPoints.clear();
	innerPoints = this->massParticles;
	for (auto n : this->neighbors) {
		for (auto mp : n->massParticles) {
			const auto distanceSquared = Math::getDistanceSquared(mp->position, p);
			if (distanceSquared < r * r) {
				innerPoints.push_back(mp);
			}
		}
	}
}

void MVPVolumeParticle::calculateDragForce()
{
	//const auto t = (temperature - 300.0f);
	const auto drag = -dragForceCoe * (velocity - Vector3df(0.0, -10, 0.0)); //* (1.0f - density / 1.0f);
	addForce(drag * this->density);
}

void MVPVolumeParticle::calculateDragHeat()
{
	this->enthaply += -dragHeatCoe * (temperature - 300.0f); //* (1.0f - density / 1.0f);
}
