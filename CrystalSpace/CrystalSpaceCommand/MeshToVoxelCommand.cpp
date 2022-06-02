#include "MeshToVoxelCommand.h"

#include "CrystalScene/Scene/PolygonMeshScene.h"
#include "../CrystalSpace/VoxelScene.h"

#include "../CrystalSpace/Voxelizer.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "MeshToVoxelCommand";
	PublicLabel PolygonMeshIdLabel = "PolygonMeshId";
	PublicLabel VoxelIdLabel = "VoxelId";
	PublicLabel DivideLengthLabel = "DivideLength";
}

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;

MeshToVoxelCommand::MeshToVoxelCommand() :
	ICommand(&args, &results)
{}

MeshToVoxelCommand::Args::Args() :
	meshId(::PolygonMeshIdLabel, -1),
	voxelId(::VoxelIdLabel, -1),
	divideLength(::DivideLengthLabel, 1.0)
{
	add(&meshId);
	add(&voxelId);
	add(&divideLength);
}

MeshToVoxelCommand::Results::Results()
{
}

std::string MeshToVoxelCommand::getName()
{
	return ::CommandNameLabel;
}

bool MeshToVoxelCommand::execute(World* scene)
{
	auto pmScene = scene->getScenes()->findSceneById<PolygonMeshScene*>(args.meshId.getValue());
	if (pmScene == nullptr) {
		return false;
	}
	auto voxelScene = scene->getScenes()->findSceneById<VoxelScene*>(args.voxelId.getValue());
	if (voxelScene == nullptr) {
		return false;
	}
	/*
	Voxelizer converter;
	converter.voxelize(*pmScene->getShape(), args.divideLength.getValue());
	auto voxel = converter.getVoxel();
	voxelScene->resetShape();
	*/
	/*
	MeshToVoxelConverter converter;
	converter.convert(*pmScene->getShape(), args.divideLength.getValue());
	auto voxel = converter.toVoxel();
	voxelScene->resetShape(std::move(voxel));
	*/
	return true;
}