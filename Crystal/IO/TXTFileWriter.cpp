#include "TXTFileWriter.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

void TXTFileWriter::add(const Vector3dd& position)
{
	positions.emplace_back(position);
}

bool TXTFileWriter::write(const std::filesystem::path& filePath)
{
	std::ofstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}

	for(const auto& p : positions) {
		stream << p.x << " " << p.y << " " << p.z << std::endl;
	}

	stream.close();
	return true;
}