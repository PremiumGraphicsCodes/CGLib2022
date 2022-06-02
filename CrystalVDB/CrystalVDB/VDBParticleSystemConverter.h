#pragma once

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class IParticleSystemScene;
	}
	namespace VDB {
		class VDBPointsScene;
		class VDBVolumeScene;

class VDBParticleSystemConverter
{
public:
	void toVolume(const VDBPointsScene& particles, const float radius, const float voxelSize, VDBVolumeScene* volume);

	void fromVDB(const VDBPointsScene& src, Scene::ParticleSystemScene* ps);

	void toVDB(const Scene::IParticleSystemScene& src, VDBPointsScene* dest);

private:
};
	}
}