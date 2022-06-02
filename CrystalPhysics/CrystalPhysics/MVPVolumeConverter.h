#pragma once

#include <vector>
#include "Crystal/Math/Vector3d.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPMassParticle.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPVolumeParticle.h"
#include "CrystalSpace/CrystalSpace/MCCell.h"
#include "CrystalSpace/CrystalSpace/MarchingCubesAlgo.h"

namespace Crystal {
	namespace Physics {

class MVPVolumeConverter
{
public:
	void build(const std::vector<MVPVolumeParticle*>& particles, const double cellLength, const double searchRadius);

	std::unique_ptr<Space::SparseVolumef> getVolume() { return std::move(sparseVolume); }

private:
	std::unique_ptr<Space::SparseVolumef> sparseVolume;
};
	}
}