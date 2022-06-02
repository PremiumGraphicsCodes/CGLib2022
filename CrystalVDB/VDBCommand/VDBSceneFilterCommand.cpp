#include "VDBSceneFilterCommand.h"

#include "../CrystalVDB/VDBFilter.h"
#include "../CrystalVDB/VDBScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneFilter";
	PublicLabel VDBSceneIdLabel = "VDBSceneId";
	PublicLabel WidthLabel = "Width";
	PublicLabel IterationLabel = "Iteration";
	PublicLabel FilterTypeLabel = "FilterType";
	PublicLabel FilterType_MedianLabel = "Median";
	PublicLabel FilterType_MeanLabel = "Mean";
	PublicLabel FilterType_GaussianLabel = "Gaussian";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneFilterCommand::Args::Args() :
	vdbSceneId(::VDBSceneIdLabel, -1),
	width(::WidthLabel, 1),
	iteration(::IterationLabel, 1),
	filterType(::FilterTypeLabel, ::FilterType_MedianLabel)
{
	add(&vdbSceneId);
	add(&width);
	add(&iteration);
	add(&filterType);
}

VDBSceneFilterCommand::Results::Results()
{
}

VDBSceneFilterCommand::VDBSceneFilterCommand() :
	ICommand(&args, &results)
{}

VDBSceneFilterCommand::VDBSceneFilterCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneFilterCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneFilterCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBScene*>(args.vdbSceneId.getValue());
	if (scene == nullptr) {
		return false;
	}

	const auto volumes = scene->getVolumes();

	for (auto volume : volumes) {
		const auto type = args.filterType.getValue();

		const auto width = args.width.getValue();
		const auto iter = args.iteration.getValue();

		VDBFilter filter;
		filter.setSource(volume);
		if (type == ::FilterType_MedianLabel) {
			filter.median(width, iter);
		}
		else if (type == ::FilterType_GaussianLabel) {
			filter.gaussian(width, iter);
		}
		else if (type == ::FilterType_MeanLabel) {
			filter.mean(width, iter);
		}
		else {
			assert(false);
		}
	}

	return true;
}