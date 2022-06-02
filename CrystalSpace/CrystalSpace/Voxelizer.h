#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "Voxel.h"

#include <vector>
#include <memory>

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace Space {

class Voxelizer
{
public:
	void voxelize(const Shape::PolygonMesh& polygon, const double res);

	//void fill();

	std::unique_ptr<Voxel> getVoxel() { return std::move(voxel); }

private:
	std::unique_ptr<Voxel> voxel;

private:
	Util::Array3d<unsigned int> scanX();

	Util::Array3d<unsigned int> scanY();

	Util::Array3d<unsigned int> scanZ();

};

	}
}