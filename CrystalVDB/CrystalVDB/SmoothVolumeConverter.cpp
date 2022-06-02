
#include "SmoothVolumeConverter.h"

#include "Crystal/Shape/IParticle.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"
#include "CrystalSpace/CrystalSpace/SparseVolumeBuilder.h"
#include "CrystalSpace/CrystalSpace/DynamicOctree.h"

#include "Crystal/Math/Sphere3d.h"
#include "VDBVolumeConverter.h"
#include "VDBVolumeImpl.h"
#include "VDBPointsImpl.h"


using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::VDB;

namespace {
	float getCubicSpline(const float distance, const float effectLength)
	{
		const auto q = distance * 2 / (effectLength);

		if (q < 1) {
			return (2.0f / 3.0f - q * q + 0.5f * q * q * q);
		}
		else if (q < 2) {
			return (std::pow(2.0f - q, 3.0f) / 6.0f);
		}
		else {
			return 0;
		}
	}
}


std::vector<VDBVolumeScene*> SmoothVolumeConverter::build(VDBPointsScene* vdbParticles, const float particleRadius, const float cellLength, const std::vector<std::string>& floatNames)
{
	std::vector<VDBVolumeScene*> vdbVolumes;

	auto vdbVolume = new VDBVolumeScene();
	vdbVolume->getImpl()->getPtr()->setName("density");
	vdbVolume->setScale(cellLength);
	auto grid = vdbVolume->getImpl()->getPtr();
	auto accessor = grid->getAccessor();

	std::vector<openvdb::FloatGrid::Accessor> floatAccessors;
	for (const auto& n : floatNames) {
		auto vdbVolume = new VDBVolumeScene();
		vdbVolume->getImpl()->getPtr()->setName(n);
		vdbVolume->setScale(cellLength);
		auto grid = vdbVolume->getImpl()->getPtr();
		vdbVolumes.push_back(vdbVolume);
		floatAccessors.push_back(grid->getAccessor());
	}

	vdbVolumes.push_back(vdbVolume);

	const auto r = static_cast<int>(particleRadius / cellLength) / 2;

	const auto names = vdbParticles->getImpl()->getAttributeNames();

	auto psGrid = vdbParticles->getImpl()->getPtr();
	for (auto leafIter = psGrid->tree().cbeginLeaf(); leafIter; ++leafIter) {
		const auto& array = leafIter->constAttributeArray("P");
		std::vector<openvdb::points::AttributeHandle<float>> floatHandles;
		for (const auto& n : floatNames) {
			const auto& fa = leafIter->constAttributeArray(n);
			floatHandles.push_back(fa);
		}

		openvdb::points::AttributeHandle<openvdb::Vec3f> positionHandle(array);
		for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
			openvdb::Vec3f voxelPosition = positionHandle.get(*indexIter);
			const auto xyz = indexIter.getCoord().asVec3d();
			openvdb::Vec3f worldPosition = psGrid->transform().indexToWorld(voxelPosition + xyz);
			auto ix = *indexIter;
			std::vector<float> floatValues;
			for (const auto& fh : floatHandles) {
				floatValues.push_back(fh.get(ix));
			}

			const auto index = grid->worldToIndex(worldPosition);
			const auto p = worldPosition;

			for (int i = -r; i <= r; ++i) {
				for (int j = -r; j <= r; ++j) {
					for (int k = -r; k <= r; ++k) {
						const auto ix = index[0] + i;
						const auto iy = index[1] + j;
						const auto iz = index[2] + k;
						const auto c = openvdb::math::Coord(ix, iy, iz);
						const auto pos = grid->indexToWorld(c);
						const auto dist = std::pow(pos[0] - p[0], 2) + std::pow(pos[1] - p[1], 2) + std::pow(pos[2] - p[2], 2);
						const auto v = ::getCubicSpline(std::sqrt(dist), particleRadius);
						const auto vv = accessor.getValue(c) + v;
						accessor.setValue(c, vv);
						for (size_t i = 0; i < floatValues.size(); ++i) {
							const auto tt = floatValues[i] * ::getCubicSpline(std::sqrt(dist), particleRadius);
							floatAccessors[i].setValue(c, tt + floatAccessors[i].getValue(c));
						}
					}
				}
			}
		}
	}

	for (auto iter = grid->cbeginValueOn(); iter.test(); ++iter) {
		const auto value = *iter;
		const auto c = iter.getCoord();
		for (auto& fa : floatAccessors) {
			const auto t = fa.getValue(c);
			fa.setValue(c, t / value);
		}
	}
	return vdbVolumes;
}
