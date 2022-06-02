#include "PLYFileReader.h"

//#include "PCDFileReader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

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

bool PLYFileReader::read(const std::filesystem::path& filename)
{
	std::ifstream stream(filename, std::ios::in | std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	return read(stream);
}

bool PLYFileReader::read(std::istream& stream)
{
	unsigned int count = 0;
	std::string str;
	bool isAscii = false;
	while (std::getline(stream, str)) {
		if (str.empty()) {
			continue;
		}
		const auto& splitted = ::split(str, ' ');
		//assert(splitted.size() >= 2);
		if (splitted[0] == "comment") {
			continue;
		}
		else if (splitted[0] == "format") {
			if (splitted[1] == "ascii") {
				isAscii = true;
			}
		}
		else if (splitted[0] == "element") {
			if (splitted[1] == "vertex") {
				count = std::stoi(splitted[2]);
			}
		}
		else if (splitted[0] == "property") {
			auto typeName = splitted[1];
			auto name = splitted[2];
			PLYProperty prop(name, PLYProperty::toType(typeName));
			ply.properties.push_back(prop);
		}
		else if (splitted[0] == "end_header") {
			break;
		}
	}

	if (isAscii) {
		return readAsciiData(stream, count);
	}
	else {
		return readBinaryData(stream, count);
	}

	return false;
}

namespace {
	template<typename T>
	T read_binary_as(std::istream& is)
	{
		T val;
		is.read(reinterpret_cast<char*>(std::addressof(val)), sizeof(T));
		return val;
	}
}

bool PLYFileReader::readAsciiData(std::istream & stream, const unsigned int count)
{
	std::string str;
	for (unsigned int i = 0; i < count; ++i) {
		std::getline(stream, str);
		const auto& splitted = ::split(str, ' ');
		PLYPoint point;
		//assert(splitted.size() >= 3);
		for (int j = 0; j < ply.properties.size(); ++j) {
			auto type = (ply.properties[j].type);
			if (type == PLYType::FLOAT) {
				point.values.push_back(std::stof(splitted[j]));
			}
		}
		ply.vertices.push_back(point);
	}
	return true;
}

bool PLYFileReader::readBinaryData(std::istream& stream, const unsigned int count)
{
	for (unsigned int i = 0; i < count; ++i) {
		PLYPoint point;
		for (int j = 0; j < ply.properties.size(); ++j) {
			auto type = (ply.properties[j].type);
			if (type == PLYType::FLOAT) {
				point.values.push_back( read_binary_as<float>(stream) );
			}
		}
		ply.vertices.push_back(point);
	}
	return true;
}