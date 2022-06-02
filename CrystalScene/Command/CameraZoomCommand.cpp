#include "CameraZoomCommand.h"

#include "Public/PublicLabel.h"

namespace CameraZoomCommandLabels
{
	PublicLabel CameraZoomCommandLabel = "CameraZoom";
	PublicLabel ZoomRatioLabel = "Ratio";
}

using namespace Crystal::Math;
using namespace Crystal::Command;

CameraZoomCommand::Args::Args() :
	ratio(CameraZoomCommandLabels::ZoomRatioLabel, 1.0)
{
	add(&ratio);
}

std::string CameraZoomCommand::getName()
{
	return CameraZoomCommandLabels::CameraZoomCommandLabel;
}

bool CameraZoomCommand::execute(Crystal::Scene::World* scene)
{
	auto camera = scene->getCamera()->getCamera();
	camera->zoom(args.ratio.getValue());
	//scene->getCamera()->getPresenter()->updateView();

	return true;
}

