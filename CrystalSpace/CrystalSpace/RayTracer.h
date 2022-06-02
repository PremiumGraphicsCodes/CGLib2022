#pragma once

#include "../../Crystal/Util/UnCopyable.h"

#include "../../Crystal/Math/Ray3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"
#include "LinearOctree.h"

namespace Crystal {
	namespace Space {

class RayTraceItem : public LinearOctreeItem
{
public:
	explicit RayTraceItem(const Math::Triangle3d& triangle) :
		LinearOctreeItem(triangle.getBoundingBox()),
		triangle(triangle)
	{}

	Math::Triangle3d getTriangle() const { return triangle; }

private:
	Math::Triangle3d triangle;
};

class RayTracer : private UnCopyable
{
public:
	void build(const Math::Box3dd& space, const int level);

	void clear();

	void add(RayTraceItem* item);

	void trace(const Math::Ray3d& ray, const double pitch);

	std::list<const LinearOctreeCell*> getCells() const { return cells; }

	const LinearOctree& getOctree() const { return octree; }

	std::list<LinearOctreeIndex> getIndices() const { return indices; }

	std::vector<Math::Vector3dd> getIntersections() const { return intersections; }

private:
	void calculateIntersections(const Math::Ray3d& ray);

	LinearOctree octree;
	std::list<const LinearOctreeCell*> cells;
	std::list<LinearOctreeIndex> indices;
	std::vector<Math::Vector3dd> intersections;
};

	}
}