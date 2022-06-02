#pragma once

namespace Crystal {
	namespace Space {
		template<typename T>
		class SparseVolume;
	}
	namespace VDB {
		class VDBVolumeScene;
		class VDBMeshScene;
		class VDBParticleSystemScene;

class VDBVolumeConverter
{
public:
	void fromSparseVolume(const Crystal::Space::SparseVolume<float>& sp, VDBVolumeScene* volume) const;
private:
};

	}
}