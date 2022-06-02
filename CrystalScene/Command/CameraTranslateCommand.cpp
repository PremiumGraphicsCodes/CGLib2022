#include "CameraTranslateCommand.h"
#include "PublicLabel.h"

namespace CameraTranslateCommandLabels
{
	PublicLabel TranslateLabel = "Translate";
	PublicLabel CameraTranslateCommandLabel = "CameraTranslate";
}

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraTranslateCommand::Args::Args() :
	translate(CameraTranslateCommandLabels::TranslateLabel, Vector3dd())
{
	add(&translate);
}

std::string CameraTranslateCommand::getName()
{
	return CameraTranslateCommandLabels::CameraTranslateCommandLabel;
}

bool CameraTranslateCommand::execute(World* scene)
{
	auto camera = scene->getCamera()->getCamera();
	const Vector3df t = args.translate.getValue();
	const auto& eye = camera->getEye();
	const auto& target = camera->getTarget();
	const auto& up = camera->getUp();
	camera->lookAt(eye + t, target + t, up);
	//scene->getCamera()->getPresenter()->updateView();

	//camera->moveTarget(args.translate.getValue());
	return true;
}
