#include "STLFileWriter.h"
#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool STLFileWriter::writeAscii(const std::filesystem::path& filePath, const STLFile& stl)
{
	std::ofstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}
	return writeAscii(stream, stl);
}

bool STLFileWriter::writeAscii(std::ostream& stream, const STLFile& stl)
{
	stream << "solid" << " " << stl.header.c_str() << std::endl;

	const auto& faces = stl.faces;
	for (const auto& face : faces) {
		stream << "facet" << " ";
		const auto& normal = face.normal;
		stream << "normal" << " " << normal.x << " " << normal.y << " " << normal.z << std::endl;
		stream << "outer loop" << std::endl;
		const auto& positions = face.triangle.getVertices();
		for (const auto& pos : positions) {
			stream << "vertex" << " " << pos.x << " " << pos.y << " " << pos.z << std::endl;
		}
		stream << "endloop" << std::endl;
		stream << "endfacet" << std::endl;
	}
	stream << "endsolid" << std::endl;

	return stream.good();
}


namespace {
	std::array<float, 3> toArrayf(const Vector3dd& v) {
		auto x = (float)(v.x);
		auto y = (float)(v.y);
		auto z = (float)(v.z);
		return { x, y, z };
	}
}

bool STLFileWriter::writeBinary(const std::filesystem::path& filePath, const STLFile& stl)
{
	std::ofstream stream(filePath, std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	return writeBinary(stream, stl);
}

bool STLFileWriter::writeBinary(std::ostream& stream, const STLFile& stl)
{
	const char* head = stl.header.c_str();
	stream.write(head, 80);

	const auto howMany = stl.faces.size();
	stream.write((char*)&howMany, sizeof(unsigned int));

	for (const auto& cell : stl.faces) {
		const auto& normal = toArrayf(cell.normal);
		stream.write((char*)&(normal.front()), sizeof(float) * 3);
		const auto& vertices = cell.triangle.getVertices();
		for (const auto& pos : vertices) {
			const auto& p = toArrayf(pos);
			stream.write((char*)&(p.front()), sizeof(float) * 3);
		}
		char padding[2];
		padding[0] = '0';
		padding[1] = '0';
		stream.write(padding, sizeof(char) * 2);
	}

	return stream.good();
}