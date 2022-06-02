#pragma once

#include <filesystem>
#include <cassert>

namespace Crystal {
	namespace IO {

enum class FileFormat
{
	STL,
	STL_ASCII,
	STL_BINARY,
	OBJ,
	MTL,
	PCD,
	NONE,
};

static FileFormat getFileFormat(const std::filesystem::path& path)
{
	const auto& ext = path.extension();
	if (ext == ".obj") {
		return FileFormat::OBJ;
	}
	else if (ext == ".mtl") {
		return FileFormat::MTL;
	}
	else if (ext == ".stl") {
		return FileFormat::STL_ASCII;
	}
	else if (ext == ".pcd") {
		return FileFormat::PCD;
	}
	else {
		assert(false);
		return FileFormat::NONE;
	}
}
	}
}