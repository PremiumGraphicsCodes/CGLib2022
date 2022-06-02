#pragma once

namespace Crystal {
	namespace VDB {
		class VDBMeshScene;
		class VDBVolumeScene;

class VDBMeshToVolumeConverter
{
public:
	static VDBVolumeScene* toVolume(const VDBMeshScene& mesh, const double divideLength);

private:
};

	}
}