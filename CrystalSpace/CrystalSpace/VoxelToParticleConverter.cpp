#include "VoxelToParticleConverter.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Circle3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

void VoxelToParticleConverter::convert(const Voxel& voxel)
{
	const auto& nodes = voxel.getNodes();
	const auto res = voxel.getResolutions();

	for (int i = 0; i < res[0]; ++i) {
		for (int j = 0; j < res[1]; ++j) {
			for (int k = 0; k < res[2]; ++k) {
				if (voxel.getValue(i, j, k)) {
					positions.push_back(voxel.getCellPosition(i, j, k));
				}
			}
		}
	}
}
