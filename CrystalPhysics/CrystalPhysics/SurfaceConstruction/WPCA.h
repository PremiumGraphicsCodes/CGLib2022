#pragma once

#include "../../../Crystal/Math/Vector3d.h"
#include "../../../Crystal/Math/Matrix3d.h"

#include "../../../Crystal/Shape/IParticle.h"
#include <vector>

namespace Crystal {
	namespace Physics {

class WPCA
{
public:
	Math::Matrix3df calculateCovarianceMatrix(Shape::IParticle* center, const std::vector<Shape::IParticle*>& positions, const float radius);

	Math::Vector3df calculateWeightedMean(Shape::IParticle* center, const std::vector<Shape::IParticle*>& positions, const float radius);

	float calculateWeight(const Math::Vector3df& lhs, const Math::Vector3df& rhs, const float radius);

	void setup(Shape::IParticle* center, const std::vector<Shape::IParticle*>& positions, const float radius);

private:
	class PositionWeight
	{
	public:
		Math::Vector3df position;
		float weight;
	};

	std::vector<PositionWeight> pws;
	float totalWeight;
};
	}
}