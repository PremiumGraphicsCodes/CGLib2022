#include "VDBToSpheres.h"

#include "openvdb/openvdb.h"
#include "openvdb/tools/VolumeToSpheres.h"
#include "CrystalVDB/CrystalVDB/VDBVolumeImpl.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

void VDBToSpheres::convert(const VDBVolumeScene* src)
{
	std::vector<openvdb::Vec4s> spheres;
	openvdb::tools::fillWithSpheres(*src->getImpl()->getPtr(), spheres);

	for (const auto& s : spheres) {
		const Sphere3df ss(Vector3df(s[0], s[1], s[2]), s[3]);
		this->spheres.push_back(ss);
	}
}
