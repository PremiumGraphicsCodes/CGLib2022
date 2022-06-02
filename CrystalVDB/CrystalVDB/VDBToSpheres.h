#pragma once

#include "VDBVolumeScene.h"
#include "Crystal/Math/Sphere3d.h"

namespace Crystal {
	namespace VDB {

class VDBToSpheres
{
public:
	void convert(const VDBVolumeScene* src);

	std::vector<Math::Sphere3df> getSpheres() const { return spheres; }

private:
	std::vector<Math::Sphere3df> spheres;
};

	}
}