#pragma once

#include "SparseVolume.h"
#include <memory>

namespace Crystal {
	namespace Math {
		template<typename T>
		class Box3d;
		template<typename T>
		class Sphere3d;
	}
	namespace Space {

class SparseVolumeBuilder
{
public:
	void build(const Math::Vector3df& cellLength, const size_t tableSize);

	void add(const Math::Box3d<double>& box);

	void add(const Math::Sphere3d<double>& sphere);

	std::unique_ptr<SparseVolumef> get() { return std::move(volume); }

private:
	std::unique_ptr<SparseVolumef> volume;
};
	}
}