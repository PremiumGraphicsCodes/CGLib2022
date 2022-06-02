#include "VDBSceneResamplingCommand.h"

#include "../CrystalVDB/VDBResampler.h"
#include "../CrystalVDB/VDBScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneResampling";
	PublicLabel SceneIdLabel = "SceneId";
	PublicLabel SamplingTypeLabel = "SamplingType";
	PublicLabel SamplingType_PointLabel = "Point";
	PublicLabel SamplingType_BoxLabel = "Box";
	PublicLabel SamplingType_QuadricLabel = "Quadric";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneResamplingCommand::Args::Args() :
	sceneId(::SceneIdLabel, -1),
	samplingType(::SamplingTypeLabel, ::SamplingType_PointLabel)
{
	add(&sceneId);
	add(&samplingType);
}

VDBSceneResamplingCommand::Results::Results()
{
}

VDBSceneResamplingCommand::VDBSceneResamplingCommand() :
	ICommand(&args, &results)
{}

VDBSceneResamplingCommand::VDBSceneResamplingCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneResamplingCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneResamplingCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBScene*>(args.sceneId.getValue());
	if (scene == nullptr) {
		return false;
	}

	const auto volumes = scene->getVolumes();
	VDBResampler resampler;
	for (const auto v : volumes) {
		resampler.setSource(v);

		const auto samplingType = args.samplingType.getValue();
		if (samplingType == ::SamplingType_PointLabel) {
			resampler.point();
		}
		else if (samplingType == ::SamplingType_BoxLabel) {
			resampler.box();
		}
		else if (samplingType == ::SamplingType_QuadricLabel) {
			resampler.quadratic();
		}
		else {
			assert(false);
			return false;
		}
	}

	return true;
}
