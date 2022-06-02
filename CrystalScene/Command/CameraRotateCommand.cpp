#include "CameraRotateCommand.h"

#include "PublicLabel.h"

namespace CameraRotateCommandLabels
{
	PublicLabel CameraRotateCommandLabel = "CameraRotate";
	PublicLabel MatrixLabel = "Matrix";
}

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraRotateCommand::Args::Args() :
	matrix(CameraRotateCommandLabels::MatrixLabel, Matrix3dd())
{
	add(&matrix);
}

std::string CameraRotateCommand::getName()
{
	return CameraRotateCommandLabels::CameraRotateCommandLabel;
}

bool CameraRotateCommand::execute(World* scene)
{
	Matrix3df matrix = args.matrix.getValue();
	auto camera = scene->getCamera()->getCamera();
	camera->rotate(matrix);
	//scene->getCamera()->getPresenter()->updateView();
	return true;
}
