#pragma once

#include <list>
#include <vector>
#include <memory>

#include "Crystal/Math/Vector3d.h"
#include "../IPhysicsParticle.h"

#include "../SPHKernel.h"
#include "../SPHConstant.h"

namespace Crystal {
	namespace Physics {
		class PBFluidScene;

class PBSPHParticle : public IPhysicsParticle
{
public:
	PBSPHParticle(const Math::Vector3df& center, const float radius, PBFluidScene* scene);

	virtual ~PBSPHParticle() {};

	float getDensityRatio() const;

	float getMass() const;

	float getVolume() const;

	float getRestVolume() const;

	void addForce(const Math::Vector3df& force) { this->force += force; }

	void setForce(const Math::Vector3df& force) { this->force = force; }

	Math::Vector3df getForce() const { return force; }

	void setDefaultDensity();

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	void init();

	Math::Vector3df getAccelaration() { return force / density; }

	Math::Vector3df getVelocity() const { return velocity; }

	void setVelocity(const Math::Vector3df& velocity) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3df& velocity) {
		this->velocity += velocity;
		//this->velocity *= 0.999;
	}

	void forwardTime(const float timeStep);

	void addExternalForce(const Math::Vector3df& force);

	void addSelfDensity();

	void addDensity(const PBSPHParticle& rhs);

	void addDensity(const float distance, const float mass);

	void predictPosition_(const float dt);

	void updatePredictPosition();

	void updateVelocity(const float dt);

	void updatePosition();

	void addPositionCorrection(const Math::Vector3df& pc);

	//void solveViscosity(const float distance);

	float getEffectLength() const;

	Math::Vector3df getPredictPosition() const { return predictPosition; }

	Math::Vector3dd getPosition() const { return position; }

	void calculatePressure(const PBSPHParticle& rhs);

	void calculateViscosity(const PBSPHParticle& rhs);

	float getConstraint() const;

	Math::Vector3df dx;
	Math::Vector3df xvisc;

	void setDensity(const float d) { this->density = d; }

	double getRadius() const { return radius; }

private:
	Math::Vector3df predictPosition;
	Math::Vector3df force;
	Math::Vector3df velocity;
	Math::Vector3df normal;

	Math::Vector3df position;
	float radius;
	float density;

	PBFluidScene* scene;

	SPHKernel* getKernel();
};

	}
}
