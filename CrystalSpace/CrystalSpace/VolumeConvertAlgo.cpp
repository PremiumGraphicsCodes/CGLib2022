#include "VolumeConvertAlgo.h"
#include "CompactSpaceHash3d.h"

#include "Octree.h"
#include "../../Crystal/Math/Gaussian1d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Space;

VolumeConvertAlgo::VolumeConvertAlgo(const Box3dd& box, const std::array<size_t, 3>& resolutions) :
	volume(box, resolutions)
{
}

void VolumeConvertAlgo::add(IParticle* particle)
{
	particles.push_back(particle);
}

void VolumeConvertAlgo::build(const double searchRadius)
{
	Gaussian1d kernel;

	CompactSpaceHash3d spaceHash(searchRadius, static_cast<int>(particles.size()));

	const auto resolutions = volume.getResolutions();

	for (int u = 0; u < resolutions[0]; ++u) {
		for (int v = 0; v < resolutions[1]; ++v) {
			for (int w = 0; w < resolutions[2]; ++w) {
				const auto& p = volume.getCellPosition(u, v, w);
				const auto& neighbors = spaceHash.findNeighbors(p);
				for (auto n : neighbors) {
					const auto distanceSquared = Crystal::Math::getDistanceSquared(p, n->getPosition());
					if (distanceSquared > searchRadius * searchRadius) {
						const auto distance = ::sqrt(distanceSquared);
						const auto value = kernel.getValue(distance / searchRadius) + volume.getValue(u,v,w);
						volume.setValue(u, v, w, value);
					}
				}
			}
		}
	}
}