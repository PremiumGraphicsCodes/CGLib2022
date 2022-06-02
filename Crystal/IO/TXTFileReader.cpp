#include "TXTFileReader.h"

#include <fstream>
#include <sstream>
#include <string>

using namespace Crystal::Math;
using namespace Crystal::IO;

namespace {
	std::vector<std::string> split(const std::string& input, char delimiter)
	{
		std::istringstream stream(input);

		std::string field;
		std::vector<std::string> result;
		while (std::getline(stream, field, delimiter)) {
			result.push_back(field);
		}
		return result;
	}
}

bool TXTFileReader::read(const std::filesystem::path& filePath)
{
	std::ifstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}
	return read(stream);
}

bool TXTFileReader::read(std::istream & stream)
{
	std::string str;
	while (std::getline(stream, str)) {
		if (str.empty()) {
			continue;
		}
		const auto& splitted = ::split(str, ' ');
		assert(splitted.size() >= 3);
		const auto x = std::stod(splitted[0]);
		const auto y = std::stod(splitted[1]);
		const auto z = std::stod(splitted[2]);
		this->positions.emplace_back(x, y, z);
	}

	return true;
}
