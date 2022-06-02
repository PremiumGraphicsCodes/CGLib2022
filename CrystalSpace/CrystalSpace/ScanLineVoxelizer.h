#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "Voxel.h"
#include "SpaceHash3d.h"
#include "Crystal/Util/Array3d.h"

#include <vector>
#include <memory>

namespace Crystal {
	namespace Shape {
		class TriangleMesh;
	}
	namespace Space {

class ScanLineVoxelizer
{
public:
	void voxelize(const std::vector<Math::Triangle3d>& triangles, const Math::Box3dd& space, const double res);

	std::unique_ptr<Voxel> getVoxel() { return std::move(voxel); }

	std::vector<Math::Vector3dd> getIntersections() const { return intersections; }

private:
	Util::Array3d<unsigned int> scanX(const Math::Box3dd& space, const std::array<size_t,3>& ress, const Math::Vector3dd& cellLength);

	Util::Array3d<unsigned int> scanY(const Math::Box3dd& space, const std::array<size_t, 3>& ress, const Math::Vector3dd& cellLength);

	Util::Array3d<unsigned int> scanZ(const Math::Box3dd& space, const std::array<size_t, 3>& ress, const Math::Vector3dd& cellLength);

	//Math::Vector3dd toPosition(const std::array<unsigned int, 3>& index) const;

	std::unique_ptr<Voxel> voxel;
	std::vector<Math::Vector3dd> intersections;
	std::unique_ptr<SpaceHash3d> table;
};

	}
}