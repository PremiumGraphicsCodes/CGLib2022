#include "CameraGetCommand.h"

#include "PublicLabel.h"

namespace CameraGetCommandLabels
{
	PublicLabel CommandNameLabel = "CameraGet";
	PublicLabel NearLabel = "Near";
	PublicLabel FarLabel = "Far";
	PublicLabel EyePositionLabel = "EyePosition";
	PublicLabel TargetPositionLabel = "TargetPosition";
	PublicLabel UpVectorLabel = "UpVector";
	PublicLabel ProjectionMatrixLabel = "ProjectionMatrix";
	PublicLabel RotationMatrixLabel = "RotationMatrix";
}


using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraGetCommand::Results::Results() :
	near(CameraGetCommandLabels::NearLabel, 0.1),
	far(CameraGetCommandLabels::FarLabel, 1.0),
	eyePosition(CameraGetCommandLabels::EyePositionLabel, Vector3dd(1,1,1)),
	targetPosition(CameraGetCommandLabels::TargetPositionLabel, Vector3dd(0,0,0)),
	upVector(CameraGetCommandLabels::UpVectorLabel, Vector3dd(0,1,0)),
	projectionMatrix(CameraGetCommandLabels::ProjectionMatrixLabel, Matrix4dd()),
	rotationMatrix(CameraGetCommandLabels::RotationMatrixLabel, Matrix4dd())
{
	add(&near);
	add(&far);
	add(&eyePosition);
	add(&targetPosition);
	add(&upVector);
	add(&projectionMatrix);
	add(&rotationMatrix);
}

std::string CameraGetCommand::getName()
{
	return CameraGetCommandLabels::CommandNameLabel;
}

bool CameraGetCommand::execute(World* scene)
{
	auto camera = scene->getCamera()->getCamera();
	results.near.setValue(camera->getNear());
	results.far.setValue(camera->getFar());
	results.eyePosition.setValue(camera->getEye());
	results.targetPosition.setValue(camera->getTarget());
	results.upVector.setValue(camera->getUp());
	results.projectionMatrix.setValue(camera->getProjectionMatrix());
	results.rotationMatrix.setValue(camera->getRotationMatrix());

	return true;
}