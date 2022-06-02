#pragma once

#include <vector>
#include <memory>

#include "Crystal/Shape/Volume.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "VDBPointsScene.h"
#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {
		class VDBVolumeScene;

class SmoothVolumeConverter
{
public:
	std::vector<VDBVolumeScene*> build(VDBPointsScene* vdbParticles, const float particleRadius, const float cellLength, const std::vector<std::string>& floatNames);

private:
};

	}
}