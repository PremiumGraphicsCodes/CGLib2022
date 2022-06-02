#pragma once

#include <string>
#include <vector>
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
    namespace VDB {
        class VDBPointsScene;
        class VDBVolumeScene;

class VDBFileWriter
{
public:
    ~VDBFileWriter();

    bool open(const std::string& filePath);

    void close();

    void writePoints(const std::string& name, VDBPointsScene* positions) const;

    void writeVolumes(const std::vector<VDBVolumeScene*>& volumes) const;

private:
};

    }
}