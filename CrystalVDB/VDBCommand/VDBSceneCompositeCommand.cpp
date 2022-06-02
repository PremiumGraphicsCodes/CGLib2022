#include "VDBSceneCompositeCommand.h"

using namespace Crystal::Command;

#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBComposite.h"
#include "../CrystalVDB/VDBScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneComposite";
	PublicLabel SceneId1Label = "SceneId1";
	PublicLabel SceneId2Label = "SceneId2";
	PublicLabel DestVolumeIdLabel = "DestVolumeId";
	PublicLabel CompositeTypeLabel = "CompositeType";
	PublicLabel CompositeType_Union = "Union";
	PublicLabel CompositeType_Difference = "Difference";
	PublicLabel CompositeType_Intersection = "Intersection";
}

//using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneCompositeCommand::Args::Args() :
	sceneId1(::SceneId1Label, -1),
	sceneId2(::SceneId2Label, -1),
	compositeType(::CompositeTypeLabel, ::CompositeType_Union)
{
	add(&sceneId1);
	add(&sceneId2);
	add(&compositeType);
}

VDBSceneCompositeCommand::Results::Results()
{
}

VDBSceneCompositeCommand::VDBSceneCompositeCommand() :
	ICommand(&args, &results)
{}

VDBSceneCompositeCommand::VDBSceneCompositeCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneCompositeCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneCompositeCommand::execute(World* world)
{
	auto scene1 = world->getScenes()->findSceneById<VDBScene*>(args.sceneId1.getValue());
	if (scene1 == nullptr) {
		return false;
	}

	auto scene2 = world->getScenes()->findSceneById<VDBScene*>(args.sceneId2.getValue());
	if (scene2 == nullptr) {
		return false;
	}

	const auto volumes1 = scene1->getVolumes();
	const auto volumes2 = scene2->getVolumes();

	const auto minCount = std::min(volumes1.size(), volumes2.size());

	VDBComposite composite;
	const auto type = args.compositeType.getValue();

	for (size_t i = 0; i < minCount; ++i) {
		auto v1 = volumes1[i];
		auto v2 = volumes2[i];

		if (type == ::CompositeType_Union) {
			composite.csgUnion(v1, v2, v1);
		}
		else if (type == ::CompositeType_Difference) {
			composite.csgDifference(v1, v2, v1);
		}
		else if (type == ::CompositeType_Intersection) {
			composite.csgIntersection(v1, v2, v1);
		}
		else {
			assert(false);
			return false;
		}
	}


	return true;
}
