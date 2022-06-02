#pragma once

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace Space {

class IOctreeItem
{
public:
	explicit IOctreeItem(const Math::Triangle3d& triangle) :
		triangle(triangle)
	{}

	virtual ~IOctreeItem() {};

	Math::Box3dd getBoundingBox() const { return triangle.getBoundingBox(); }

	Math::Triangle3d getTriangle() const { return triangle; }

private:
	Math::Triangle3d triangle;
};

	}
}