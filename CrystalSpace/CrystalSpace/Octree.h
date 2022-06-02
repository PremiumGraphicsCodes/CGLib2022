#pragma once

#include <array>
#include <vector>
#include <list>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Util/UnCopyable.h"

#include "IOctreeItem.h"

namespace Crystal {
	namespace Space {

class Octree : private UnCopyable
{
public:
	Octree() : level(0)
	{};

	Octree(const Math::Box3dd& space, const int level);

	void add(IOctreeItem* item);

	void createChildren();

	bool isEmpty() const;

	std::vector<IOctreeItem*> getItems() const { return items; }

	std::vector<Octree*> getChildren() const { return children; }

	Math::Box3dd getSpace() const { return space; }

	std::list<Octree*> toSerialList();

private:
	std::vector<IOctreeItem*> items;
	std::vector<Octree*> children;
	Math::Box3dd space;
	const int level;
};

	}
}