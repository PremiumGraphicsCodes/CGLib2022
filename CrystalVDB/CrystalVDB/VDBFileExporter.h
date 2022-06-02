#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBScene;

class VDBFileExporter
{
public:
	enum class Format
	{
		PLY,
		PCD,
		STL,
		OBJ
	};

	explicit VDBFileExporter(const VDBScene* scene) :
		scene(scene)
	{}

	bool write(const std::string& filePath, const Format format);

	bool writePLY(const std::string& filePath);

	bool writePCD(const std::string& filePath);

	bool writeSTL(const std::string& filePath);

	bool writeOBJ(const std::string& filePath);

private:
	const VDBScene* scene;
};
	}
}