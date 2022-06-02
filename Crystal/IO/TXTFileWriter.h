#pragma once

#include <filesystem>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

class TXTFileWriter
{
public:
	void add(const Math::Vector3dd& position);

	bool write(const std::filesystem::path& filePath);

private:
	std::vector<Math::Vector3dd> positions;
};

	}
}