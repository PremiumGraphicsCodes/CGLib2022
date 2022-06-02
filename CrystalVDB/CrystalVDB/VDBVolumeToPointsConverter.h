#pragma once

namespace Crystal {
	namespace VDB {
		class VDBVolumeScene;
		class VDBPointsScene;

class VDBVolumeToPointsConverter
{
public:
	static VDBPointsScene* toPoints(const VDBVolumeScene& volume);

private:
};

	}
}