#pragma once

#include "IShape.h"

#include "Particle.h"

#include <vector>

namespace Crystal {
	namespace Shape {

class IParticleSystem : public IShape
{
public:
	~IParticleSystem()
	{
	}

	virtual std::vector<IParticle*> getIParticles() const = 0;

	virtual std::vector<Math::Vector3dd> getPositions() const = 0;
};

	}
}