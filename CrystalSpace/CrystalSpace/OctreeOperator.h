#pragma once

#include "Octree.h"

namespace Crystal {
	namespace Space {

class OctreeOperator
{
public:
	OctreeOperator(const Math::Box3dd& space, const float minSize);

	void add(IOctreeItem* item);

private:
	Octree root;
	float minSize;

};

	}
}