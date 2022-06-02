#include "VoxelToPSCommand.h"

#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "../CrystalSpace/VoxelScene.h"

#include "../CrystalSpace/VoxelToParticleConverter.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "VoxelToPSCommand";
	PublicLabel VoxelIdLabel = "VoxelId";
	PublicLabel PSIdLabel = "PSId";
}

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Scene;

VoxelToPSCommand::VoxelToPSCommand() :
	ICommand(&args, &results)
{}

VoxelToPSCommand::Args::Args() :
	voxelId(::VoxelIdLabel, -1),
	psId(::PSIdLabel, 1.0)
{
	add(&voxelId);
	add(&psId);
}

VoxelToPSCommand::Results::Results()
{
}

std::string VoxelToPSCommand::getName()
{
	return ::CommandNameLabel;
}

bool VoxelToPSCommand::execute(World* scene)
{
	auto voxelScene = scene->getScenes()->findSceneById<VoxelScene*>(args.voxelId.getValue());
	if (voxelScene == nullptr) {
		return false;
	}
	auto psScene = scene->getScenes()->findSceneById<ParticleSystemScene*>(args.psId.getValue());
	if (psScene == nullptr) {
		return false;
	}
	VoxelToParticleConverter converter;
	converter.convert(*voxelScene->getShape());
	const auto positions = converter.getPositions();
	auto ps = std::make_unique< ParticleSystem<ParticleAttribute>>();
	ParticleAttribute attr;
	attr.color = ColorRGBAf(0, 0, 0, 0);
	attr.size = 10.0;
	for (const auto& p : positions) {
		ps->add(p, attr);
	}
	psScene->resetShape(std::move(ps));
	return true;
}