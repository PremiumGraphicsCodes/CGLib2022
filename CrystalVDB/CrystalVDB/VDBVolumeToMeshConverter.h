#pragma once

#include "VDBMeshScene.h"
#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {

class VDBVolumeToMeshConverter
{
public:
	static VDBMeshScene* toMesh(const VDBVolumeScene& volume, const double threshold, const double adaptivity);
};
	}
}