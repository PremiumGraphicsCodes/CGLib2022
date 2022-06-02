#pragma once

#include "../../../Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {

class IPhysicsParticle : public Shape::IParticle
{
protected:
	virtual ~IPhysicsParticle() {};

	virtual void init() = 0;

	virtual void forwardTime(const float timeStep) = 0;

	virtual void addExternalForce(const Math::Vector3df& force) = 0;

};

	}
}