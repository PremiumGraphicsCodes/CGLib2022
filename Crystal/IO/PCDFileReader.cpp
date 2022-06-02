#include "PCDFileReader.h"
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

	template<typename T>
	T read_binary_as(std::istream& is)
	{
		T val;
		is.read(reinterpret_cast<char*>(std::addressof(val)), sizeof(T));
		return val;
	}
}

bool PCDFileReader::readAscii(const std::filesystem::path& filename)
{
	std::ifstream stream(filename, std::ios::in | std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	return readAscii(stream);
}

bool PCDFileReader::readAscii(std::istream& stream)
{
	this->pcd.header = readHeader(stream);
	this->pcd.data = readDataAscii(stream);
	return true;
}

PCDFile::Header PCDFileReader::readHeader(std::istream& stream)
{
	PCDFile::Header header;
	std::string str;
	while (std::getline(stream, str)) {
		if (str.empty()) {
			continue;
		}
		if (str[0] == '#') {
			continue;
		}
		const auto& splitted = ::split(str, ' ');
		assert(splitted.size() >= 2);
		if (splitted[0] == "VERSION") {
			//this->version = splitted[1];
			continue;
		}
		else if (splitted[0] == "FIELDS") {
			continue;
		}
		else if (splitted[0] == "POINTS") {
			header.points = std::stoi(splitted[1]);
		}
		else if (splitted[0] == "DATA") {
			header.isBinary = (splitted[1] == "binary");
			return header;
		}
	}

	return header;
}

PCDFile::Data PCDFileReader::readDataAscii(std::istream& stream)
{
	PCDFile::Data data;

	std::string str;
	while (std::getline(stream, str)) {
		const auto& splitted = ::split(str, ' ');
		assert(splitted.size() >= 3);
		const auto x = std::stod(splitted[0]);
		const auto y = std::stod(splitted[1]);
		const auto z = std::stod(splitted[2]);
		data.positions.push_back(Vector3dd(x, y, z));
	}

	return data;
}

bool PCDFileReader::readBinary(const std::filesystem::path& filename)
{
	std::ifstream stream(filename, std::ios_base::in | std::ios_base::binary);
	if (!stream.is_open()) {
		return false;
	}
	return readBinary(stream);
}

bool PCDFileReader::readBinary(std::istream& stream)
{
	this->pcd.header = readHeader(stream);
	this->pcd.data = readDataBinary(stream, this->pcd.header.points);
	return true;
}

PCDFile::Data PCDFileReader::readDataBinary(std::istream& stream, const int howMany)
{
	PCDFile::Data data;

	for (int i = 0; i < howMany; ++i) {
		const auto x = ::read_binary_as<float>(stream);
		const auto y = ::read_binary_as<float>(stream);
		const auto z = ::read_binary_as<float>(stream);
		const auto c = ::read_binary_as<float>(stream);
		data.positions.push_back(Vector3dd(x, y, z));
	}

	return data;
}