#include "MVPMassParticle.h"

#include "MVPVolumeParticle.h"
#include "MVPFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPMassParticle::MVPMassParticle(MVPVolumeParticle* parent, const Math::Vector3df& point, const float mass) :
	parent(parent),
	vector(point),
	mass(mass),
	temperature(300.0),
	heatDiffuseCoe(0.0f)
//	pressureCoe(parent->getScene()->getPressureCoe()),
//	viscosityCoe(parent->getScene()->getViscosityCoe())
{
	updatePosition(parent->getPositionf());
	updateVelocity(parent->getVelocity());
}


Vector3dd MVPMassParticle::getPosition() const
{
	return position;
}

Vector3df MVPMassParticle::getVelocity() const
{
	return velocity;
}

void MVPMassParticle::updatePosition(const Vector3df& parentPosition)
{
	//const auto v = (parent->getPositionf() - this->position);
	this->position = parentPosition + parent->getRadius() * vector;

	//const auto vv = glm::cross(vector, parent->getVorticity()) * 0.00f;
	//this->position += vv;

	//this->vector += vv;
	//this->vector = glm::normalize(this->vector);

}

void MVPMassParticle::updateVelocity(const Vector3df& parentVelocity)
{
	this->velocity = parentVelocity;
	/*
	if (Math::getLength(parent->getVorticity()) > 1.0e-3) {
		this->velocity += glm::cross(parent->getVorticity(), vector);
	}
	*/
}

/*
void MVPMassParticle::updateVector(const float dt)
{
	const auto l = Math::getLength(vector);
	const auto vv = glm::cross(parent->getVorticity(), vector) * dt;
	this->vector += vv;
	this->vector = glm::normalize(this->vector) * l;
}
*/
