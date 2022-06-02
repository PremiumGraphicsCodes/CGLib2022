#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;

class PCDFileExporter
{
public:
	bool exportPCD(const std::experimental::filesystem::path& filePath, ParticleSystemScene& objects);
};

	}
}