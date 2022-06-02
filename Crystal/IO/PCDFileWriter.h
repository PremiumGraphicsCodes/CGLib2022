#pragma once

#include <string>
#include <filesystem>
#include "PCDFile.h"

namespace Crystal {
	namespace IO {

class PCDFileWriter
{
public:
	bool writeAscii(std::ostream& stream, const PCDFile& pcd);

	bool writeAscii(const std::filesystem::path& filename, const PCDFile& pcd);

private:
	bool writeAscii(std::ostream& stream, const PCDFile::Header& header);

	bool writeAscii(std::ostream& stream, const PCDFile::Data& data);

public:
	bool writeBinary(std::ostream& stream, const PCDFile& pcd);

	bool writeBinary(const std::filesystem::path& filename, const PCDFile& pcd);

private:
	bool writeBinary(std::ostream& stream, const PCDFile::Header& header);

	bool writeBinary(std::ostream& stream, const PCDFile::Data& data);
};

	}
}