#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBScene;

class VDBFileImporter
{
public:
	enum class Format
	{
		NONE,
		PLY,
		PCD,
		STL,
		OBJ
	};

	VDBScene* read(const std::string& filePath, const Format format);

	VDBScene* readPLY(const std::string& filePath);

	VDBScene* readPCD(const std::string& filePath);

	VDBScene* readOBJ(const std::string& filePath);

	VDBScene* readSTL(const std::string& filePath);
};
	}
}