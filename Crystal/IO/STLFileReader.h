#pragma once

#include <filesystem>
#include "STLFile.h"

namespace Crystal {
	namespace IO {

class STLFileReader
{
public:
	static bool isBinary(const std::filesystem::path& filePath);

	static bool isBinary(std::istream& in);

	bool readAscii(const std::filesystem::path& filePath);

	bool readAscii(std::istream& stream);

	bool readBinary(const std::filesystem::path& filePath);

	bool readBinary(std::istream& stream);

	STLFile getSTL() const { return stl; }

private:
	STLFile stl;
};

	}
}