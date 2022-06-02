#pragma once

#include <string>
#include <filesystem>

#include "PLYFile.h"

namespace Crystal {
	namespace IO {

class PLYFileWriter
{
public:
	bool writeASCII(const std::filesystem::path& filename, const PLYFile& pcd);

	bool writeASCII(std::ostream& stream, const PLYFile& pcd);

	bool writeBinary(const std::filesystem::path& filename, const PLYFile& pcd);

	bool writeBinary(std::ostream& stream, const PLYFile& pcd);


private:
	//bool write(std::ostream& stream, const PCDFile::Header& header);

	//bool write(std::ostream& stream, const PCDFile::Data& data);

private:
};

	}
}