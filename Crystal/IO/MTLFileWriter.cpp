#include "MTLFileWriter.h"
#include <fstream>

using namespace Crystal::IO;

bool MTLFileWriter::write(const std::filesystem::path& filePath, const MTLFile& mtl)
{
	std::ofstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}
	return write(stream, mtl);
}

bool MTLFileWriter::write(std::ostream& stream, const MTLFile& mtl)
{
	const auto& materials = mtl.materials;
	for (const auto& m : materials) {
		stream << "newmtl " << m.name << std::endl;
		stream << "Ka " << m.ambient.r << " " << m.ambient.g << " " << m.ambient.b << std::endl;
		stream << "Kd " << m.diffuse.r << " " << m.diffuse.g << " " << m.diffuse.b << std::endl;
		stream << "Ks " << m.specular.r << " " << m.specular.g << " " << m.specular.b << std::endl;
		stream << "Ns " << m.specularExponent << std::endl;
		stream << "Tr " << m.transparent << std::endl;
	}

	return true;

}
