#pragma once

#include <string>
#include <filesystem>

#include "PCDFile.h"

namespace Crystal {
	namespace IO {

class PCDFileReader
{
public:
	bool readAscii(std::istream& stream);

	bool readAscii(const std::filesystem::path& filename);

	bool readBinary(std::istream& stream);

	bool readBinary(const std::filesystem::path& filename);

	PCDFile getPCD() const { return pcd; }

private:
	PCDFile::Header readHeader(std::istream& stream);

	PCDFile::Data readDataAscii(std::istream& stream);

	PCDFile::Data readDataBinary(std::istream& stream, const int howMany);
	
private:
	bool isOk;
	PCDFile pcd;
};

	}
}