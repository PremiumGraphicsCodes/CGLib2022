#pragma once

#include "STLFile.h"
#include <filesystem>

namespace Crystal {
	namespace IO {

class STLFileWriter
{
public:
	bool writeAscii(const std::filesystem::path& filePath, const STLFile& stl);

	bool writeAscii(std::ostream& stream, const STLFile& stl);

	bool writeBinary(const std::filesystem::path& filePath, const STLFile& stl);

	bool writeBinary(std::ostream& stream, const STLFile& stl);

private:
};
	}
}