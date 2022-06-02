#pragma once

#include <filesystem>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

class TXTFileReader
{
public :
	bool read(const std::filesystem::path& filePath);

	bool read(std::istream& stream);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

private:
	std::vector<Math::Vector3dd> positions;
};
	}
}