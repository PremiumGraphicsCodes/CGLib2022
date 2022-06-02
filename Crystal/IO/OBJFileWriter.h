#pragma once

#include "OBJFile.h"
#include <filesystem>

namespace Crystal {
	namespace IO {

class OBJFileWriter
{
public:
	bool write(const std::filesystem::path& filePath, const OBJFile& obj);

	bool write(std::ostream& stream, const OBJFile& obj);

private:
};

	}
}
