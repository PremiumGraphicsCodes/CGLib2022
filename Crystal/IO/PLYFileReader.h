#pragma once

#include <string>
#include <filesystem>

#include "../Math/Vector3d.h"
#include "PLYFile.h"

namespace Crystal {
	namespace IO {

class PLYFileReader
{
public:
	bool read(const std::filesystem::path& filename);

	bool read(std::istream& stream);

	PLYFile getPLY() const { return ply; }

private:
	bool readAsciiData(std::istream& stream, const unsigned int count);

	bool readBinaryData(std::istream& stream, const unsigned int count);

private:
	PLYFile ply;
};
	}
}