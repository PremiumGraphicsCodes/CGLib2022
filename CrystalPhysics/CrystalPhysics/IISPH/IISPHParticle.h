#pragma once

#include "../SPHKernel.h"
#include "Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {

class IISPHParticle : public Shape::IParticle
{
public:
	Math::Vector3dd getPosition() const { return position; }

private:
	Math::Vector3df position;
};
	}
}