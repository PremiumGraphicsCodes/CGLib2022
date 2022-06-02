#include "VoxelSetCommand.h"

#include "../CrystalSpace/VoxelScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "VoxelNodeSet";
	PublicLabel VoxelIdLabel = "VoxelId";
	PublicLabel ResolutionXLabel = "ResolutionX";
	PublicLabel ResolutionYLabel = "ResolutionY";
	PublicLabel ResolutionZLabel = "ResolutionZ";
	PublicLabel BoundingBoxLabel = "BoundingBox";
	PublicLabel ValuesLabel = "Values";
}


using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::Command;

VoxelSetCommand::Args::Args() :
	voxelId(::VoxelIdLabel, -1),
	resX(::ResolutionXLabel, 2),
	resY(::ResolutionYLabel, 2),
	resZ(::ResolutionZLabel, 2),
	bb(::BoundingBoxLabel, Box3dd()),
	values(::ValuesLabel, {})
{
	add(&voxelId);
	add(&resX);
	add(&resY);
	add(&resZ);
	add(&bb);
	add(&values);
}

VoxelSetCommand::Results::Results()// :
//	newId(::NewIdLabel, -1)
{
	//	add(&newId);
}

std::string VoxelSetCommand::getName()
{
	return ::CommandNameLabel;
}

bool VoxelSetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VoxelScene*>(args.voxelId.getValue());
	if (scene == nullptr) {
		return false;
	}

	//auto shape = scene->getShape();
	const auto bb = args.bb.getValue();
	const std::array<size_t, 3> ress =
	{
		(size_t)args.resX.getValue(),
		(size_t)args.resY.getValue(),
		(size_t)args.resZ.getValue()
	};
	const auto values = args.values.getValue();

	assert((ress[0] * ress[1] * ress[2]) == values.size());

	auto voxel = std::make_unique<Voxel>(bb, ress);

	int index = 0;
	for (int i = 0; i < ress[0]; ++i) {
		for (int j = 0; j < ress[1]; ++j) {
			for (int k = 0; k < ress[2]; ++k) {
				voxel->setValue(i, j, k, values[index++]);
			}
		}
	}
	scene->resetShape(std::move(voxel));

	return true;
}
