#include "PLYFileWriter.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool PLYFileWriter::writeASCII(const std::filesystem::path& filename, const PLYFile& pcd)
{
	std::ofstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	return writeASCII(stream, pcd);
}

bool PLYFileWriter::writeASCII(std::ostream& stream, const PLYFile& pcd)
{
	stream << "ply" << std::endl;
	stream << "format ascii 1.0" << std::endl;
	stream << "comment " << std::endl;
	stream << "comment " << std::endl;
	stream << "obj_info " << std::endl;
	stream << "element vertex " << pcd.vertices.size() << std::endl;
	for (const auto& prop : pcd.properties) {
		stream << "property " << prop.getTypeName() << " " << prop.name << " " << std::endl;
	}
	stream << "end_header " << std::endl;

	const auto& positions = pcd.vertices;
	for (const auto& p : positions) {
		for (size_t i = 0; i < pcd.properties.size(); ++i) {
			if (pcd.properties[i].type == PLYType::FLOAT) {
				stream << p.getValueAs<float>(i) << " ";
			}
			else if (pcd.properties[i].type == PLYType::INT) {
				stream << p.getValueAs<int>(i) << " ";
			}
		}
		stream << std::endl;
	}
	return true;
}

bool PLYFileWriter::writeBinary(const std::filesystem::path& filename, const PLYFile& pcd)
{
	std::ofstream stream(filename, std::ios::out | std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	return writeBinary(stream, pcd);
}

namespace {
	bool isLittleEndian()
	{
		int x = 1;   // 0x00000001

		if (*(char*)&x) {
			// yƒAzlittle endian. memory image 01 00 00 00
			return true;
		}
		else {
			// yƒCz   big endian. memory image 00 00 00 01
			return false;
		}
	}
}

#include <iostream>

bool PLYFileWriter::writeBinary(std::ostream& stream, const PLYFile& pcd)
{
	const auto isLittleEndian = ::isLittleEndian();

	stream << "ply" << std::endl;
	if (isLittleEndian) {
		stream << "format binary_little_endian 1.0" << std::endl;
	}
	else {
		stream << "format binary_big_endian 1.0" << std::endl;
	}
	stream << "comment " << std::endl;
	stream << "comment " << std::endl;
	stream << "obj_info " << std::endl;
	stream << "element vertex " << pcd.vertices.size() << std::endl;
	for (const auto& prop : pcd.properties) {
		stream << "property " << prop.getTypeName() << " " << prop.name << " " << std::endl;
	}

	stream << "end_header " << std::endl;

	const auto& positions = pcd.vertices;
	for (const auto& p : positions) {
		for (size_t i = 0; i < pcd.properties.size(); ++i) {
			float f = p.getValueAs<float>(i);
			stream.write((char*)&f, sizeof(float));
		}
	}
	return true;

}
