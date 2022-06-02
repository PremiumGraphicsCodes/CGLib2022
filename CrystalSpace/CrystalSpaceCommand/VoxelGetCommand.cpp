#include "VoxelGetCommand.h"

#include "../CrystalSpace/VoxelScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "VoxelGet";
	PublicLabel VoxelIdLabel = "VoxelId";
	PublicLabel ResolutionXLabel = "ResX";
	PublicLabel ResolutionYLabel = "ResY";
	PublicLabel ResolutionZLabel = "ResZ";
	PublicLabel BoundingBoxLabel = "BoundingBox";
	PublicLabel ValuesLabel = "Values";
}

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;
using namespace Crystal::Command;

VoxelGetCommand::Args::Args() :
	voxelId(::VoxelIdLabel, -1)
{
	add(&voxelId);
}

VoxelGetCommand::Results::Results() :
	resX(::ResolutionXLabel, 0),
	resY(::ResolutionYLabel, 0),
	resZ(::ResolutionZLabel, 0),
	boundingBox(::BoundingBoxLabel, Box3dd()),
	values(::ValuesLabel, {})
{
	add(&resX);
	add(&resY);
	add(&resZ);
	add(&boundingBox);
	add(&values);
}

std::string VoxelGetCommand::getName()
{
	return ::CommandNameLabel;
}

bool VoxelGetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VoxelScene*>(args.voxelId.getValue());
	if (scene == nullptr) {
		return false;
	}

	auto shape = scene->getShape();

	const auto res = shape->getResolutions();
	std::vector<bool> values;
	for (int i = 0; i < res[0]; ++i) {
		for (int j = 0; j < res[1]; ++j) {
			for (int k = 0; k < res[2]; ++k) {
				values.push_back(shape->getValue(i, j, k));
			}
		}
	}

	results.resX.setValue((int)res[0]);
	results.resY.setValue((int)res[1]);
	results.resZ.setValue((int)res[2]);
	results.boundingBox.setValue(shape->getBoundingBox());
	results.values.setValue(values);
	return true;
}
