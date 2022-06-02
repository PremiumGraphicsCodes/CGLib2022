#include "VoxelizerCommand.h"

#include "CrystalScene/Scene/TriangleMeshScene.h"
#include "CrystalScene/Scene/VoxelScene.h"

#include "../CrystalSpace/ScanLineVoxelizer.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace VoxelizerLabels {
	PublicLabel CommandNameLabel = "VoxelizerCommand";
	PublicLabel MeshIdLabel = "MeshId";
	PublicLabel VoxelIdLabel = "VoxelId";
	PublicLabel DivideLengthLabel = "DivideLength";
}

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Space;
using namespace Crystal::Scene;

VoxelizerCommand::VoxelizerCommand() :
	ICommand(&args, &results)
{}

VoxelizerCommand::Args::Args() :
	meshId(VoxelizerLabels::MeshIdLabel, -1),
	voxelId(VoxelizerLabels::VoxelIdLabel, -1),
	divideLength(VoxelizerLabels::DivideLengthLabel, 1.0)
{
	add(&meshId);
	add(&voxelId);
	add(&divideLength);
}

VoxelizerCommand::Results::Results()
{
}

std::string VoxelizerCommand::getName()
{
	return VoxelizerLabels::CommandNameLabel;
}

bool VoxelizerCommand::execute(World* scene)
{
	auto pmScene = scene->getScenes()->findSceneById<TriangleMeshScene*>(args.meshId.getValue());
	if (pmScene == nullptr) {
		return false;
	}
	auto voxelScene = scene->getScenes()->findSceneById<VoxelScene*>(args.voxelId.getValue());
	if (voxelScene == nullptr) {
		return false;
	}
	if (pmScene->getShape()->getFaces().empty()) {
		return false;
	}
	const auto divideLength = args.divideLength.getValue();
	const auto bb = pmScene->getShape()->getBoundingBox();
	const auto p1 = bb.getMin() - Vector3dd(divideLength);
	const auto p2 = bb.getMax() + Vector3dd(divideLength);

	const auto faces = pmScene->getShape()->getFaces();
	std::vector<Triangle3d> triangles;
	for (const auto& f : faces) {
		triangles.emplace_back(f.triangle);
	}

	const Math::Box3dd space(p1, p2);
	ScanLineVoxelizer converter;
	converter.voxelize(triangles, space, divideLength);
	voxelScene->setShape(converter.getVoxel());
	return true;
}