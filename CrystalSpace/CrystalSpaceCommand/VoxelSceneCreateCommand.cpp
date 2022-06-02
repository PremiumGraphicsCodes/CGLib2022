#include "VoxelSceneCreateCommand.h"

#include "../CrystalSpace/VoxelScene.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "VoxelSceneCreate";
	PublicLabel ResolutionXLabel = "ResolutionX";
	PublicLabel ResolutionYLabel = "ResolutionY";
	PublicLabel ResolutionZLabel = "ResolutionZ";
	PublicLabel BoundingBoxLabel = "BoundingBox";
	PublicLabel NameLabel = "Name";
	PublicLabel NewIdLabel = "NewId";
}


using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Scene;

VoxelSceneCreateCommand::Args::Args() :
	resolutionX(::ResolutionXLabel, 10),
	resolutionY(::ResolutionYLabel, 10),
	resolutionZ(::ResolutionZLabel, 10),
	boundingBox(::BoundingBoxLabel, Box3dd()),
	name(::NameLabel, std::string(""))
{
	add(&resolutionX);
	add(&resolutionY);
	add(&resolutionZ);
	add(&boundingBox);
	add(&name);
}

VoxelSceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, -1)
{
	add(&newId);
}

std::string VoxelSceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

bool VoxelSceneCreateCommand::execute(World* world)
{
	auto name = args.name.getValue();

	const auto bb = args.boundingBox.getValue();
	const std::array<size_t, 3> res =
	{
		(size_t)args.resolutionX.getValue(),
		(size_t)args.resolutionY.getValue(),
		(size_t)args.resolutionZ.getValue()
	};
	auto shape = std::make_unique<Voxel>(bb, res);
	auto scene = new VoxelScene(world->getNextSceneId(), name, std::move(shape));
	world->addScene(scene);
	results.newId.setValue(scene->getId());
	return true;
}