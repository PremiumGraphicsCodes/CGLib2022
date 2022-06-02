#pragma once

#include "OBJFile.h"
#include <filesystem>

namespace Crystal {
	namespace IO {

class OBJFileReader
{
public:

	bool read(const std::filesystem::path& filePath);

	bool read(std::istream& stream);

	OBJFile getOBJ() const { return obj; }

private:

	Math::Vector3df readVertices(const std::vector<std::string>& strs);

	Math::Vector3df readVector3d(const std::vector<std::string>& strs);

	Math::Vector2df readVector2d(const std::vector<std::string>& strs);

	OBJFile obj;
};

	}
}
