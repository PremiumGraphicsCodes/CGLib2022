#include "PCDFileExporter.h"

#include "Scene.h"

#include "../IO/PCDFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Scene;

bool PCDFileExporter::exportPCD(const std::experimental::filesystem::path& filePath, ParticleSystemScene& scene)
{
	/*
	const auto& positions = scene.getShape()->getParticles();
	PCDFile pcd;
	pcd.header.points = positions.size();
	pcd.header.width = positions.size();
	pcd.data.positions = std::vector<Vector3dd>(positions.begin(), positions.end());
	PCDFileWriter writer;
	return writer.write(filePath, pcd);
	*/
	return false;
}