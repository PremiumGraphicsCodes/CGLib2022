#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Triangle3d.h"

namespace Crystal {
	namespace Space {

class DistanceCalculator
{
public :
	static double getDistance(const Math::Triangle3d& triangle, const Math::Vector3dd& position);
};
	}
}