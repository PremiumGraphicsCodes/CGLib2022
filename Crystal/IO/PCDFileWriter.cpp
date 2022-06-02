#include "PCDFileWriter.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool PCDFileWriter::writeAscii(const std::filesystem::path& filename, const PCDFile& pcd)
{
	std::ofstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	return writeAscii(stream, pcd);
}

bool PCDFileWriter::writeAscii(std::ostream& stream, const PCDFile& pcd)
{
	if (!writeAscii(stream, pcd.header)) {
		return false;
	}
	if (!writeAscii(stream, pcd.data)) {
		return false;
	}
	return true;
}

bool PCDFileWriter::writeAscii(std::ostream& stream, const PCDFile::Header& header)
{
	stream
		<< "# .PCD v.7 - Point Cloud Data file format" << std::endl
		<< "VERSION "
		<< ".7" << std::endl
		<< "FIELDS "
		<< "x y z rgb" << std::endl
		<< "SIZE "
		<< "4 4 4 4" << std::endl
		<< "TYPE "
		<< "F F F F" << std::endl
		<< "COUNT "
		<< "1 1 1 1" << std::endl
		<< "WIDTH "
		<< header.width << std::endl
		<< "HEIGHT "
		<< "1" << std::endl
		<< "VIEWPOINT "
		<< "0 0 0 1 0 0 0" << std::endl
		<< "POINTS "
		<< header.points << std::endl
		<< "DATA "
		<< "ascii" << std::endl;

	return true;
}

bool PCDFileWriter::writeAscii(std::ostream& stream, const PCDFile::Data& data)
{
	const auto& positions = data.positions;
	for (const auto& p : positions) {
		const float color = 0.0f;
		stream << p.x << " " <<  p.y << " " <<  p.z << " " << color << std::endl;
	}
	return true;
}


bool PCDFileWriter::writeBinary(const std::filesystem::path& filename, const PCDFile& pcd)
{
	std::fstream stream;
	stream.open(filename, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
	if (!stream.is_open()) {
		return false;
	}
	return writeBinary(stream, pcd);
}

bool PCDFileWriter::writeBinary(std::ostream& stream, const PCDFile& pcd)
{
	if (!writeBinary(stream, pcd.header)) {
		return false;
	}
	if (!writeBinary(stream, pcd.data)) {
		return false;
	}
	return true;
}


bool PCDFileWriter::writeBinary(std::ostream& stream, const PCDFile::Header& header)
{
	stream
		<< "# .PCD v.7 - Point Cloud Data file format" << std::endl
		<< "VERSION "
		<< ".7" << std::endl
		<< "FIELDS "
		<< "x y z rgb" << std::endl
		<< "SIZE "
		<< "4 4 4 4" << std::endl
		<< "TYPE "
		<< "F F F F" << std::endl
		<< "COUNT "
		<< "1 1 1 1" << std::endl
		<< "WIDTH "
		<< header.width << std::endl
		<< "HEIGHT "
		<< "1" << std::endl
		<< "VIEWPOINT "
		<< "0 0 0 1 0 0 0" << std::endl
		<< "POINTS "
		<< header.points << std::endl
		<< "DATA "
		<< "binary" << std::endl;

	return true;
}

bool PCDFileWriter::writeBinary(std::ostream& stream, const PCDFile::Data& data)
{
	const auto& positions = data.positions;
	for (const auto& p : positions) {
		const float color = 0.0f;
		const float px = static_cast<float>(p.x);
		const float py = static_cast<float>(p.y);
		const float pz = static_cast<float>(p.z);
		stream.write((char*)&px, sizeof(px));
		stream.write((char*)&py, sizeof(py));
		stream.write((char*)&pz, sizeof(pz));
		stream.write((char*)&color, sizeof(float));
	}
	return true;
}
