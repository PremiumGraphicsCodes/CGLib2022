#pragma once

#include "../../CrystalSpace/CrystalSpace/Voxel.h"
#include <vector>

namespace Crystal {
	namespace Space {

class VoxelToParticleConverter
{
public:
	//VoxelToParticleConverter();

	void convert(const Voxel& voxel);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

private:
	std::vector<Math::Vector3dd> positions;
};

	}
}