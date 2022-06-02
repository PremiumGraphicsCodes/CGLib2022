#include "OctreeOperator.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

OctreeOperator::OctreeOperator(const Box3dd& space, const float minSize) :
	root(space, 0),
	minSize(minSize)
{
}

void OctreeOperator::add(IOctreeItem* item)
{
	root.add(item);
}
