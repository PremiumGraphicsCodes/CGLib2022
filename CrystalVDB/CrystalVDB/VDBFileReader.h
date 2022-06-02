#pragma once

#include <string>
#include <vector>

#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace VDB {
        class VDBPointsScene;
        class VDBVolumeScene;

class VDBFileReader
{
public:
    VDBFileReader() {}

    ~VDBFileReader();

    bool open(const std::string& filename);

    void close();

    void readMetaData();

    std::vector<std::string> getPointNames() const { return pointNames; }

    std::vector<std::string> getGridNames() const { return floatGridNames; }

    VDBPointsScene* readPositions(const std::string& pointName, const float radius);

    VDBVolumeScene* readVolume(const std::string& volumeName);

private:
    std::vector<std::string> pointNames;
    std::vector<std::string> floatGridNames;
};

    }
}