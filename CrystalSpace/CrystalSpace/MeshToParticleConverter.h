#pragma once

#include "../../Crystal/Shape/PolygonMesh.h"

namespace Crystal {
	namespace Space {

class MeshToParticleConverter
{
public:
	void subdivide(const Shape::PolygonMesh& mesh, const double divideLength);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

private:
	std::vector<Math::Vector3dd> positions;
	
};
	}
}