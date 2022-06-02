#include "CameraSetCommand.h"

#include "PublicLabel.h"

namespace CameraSetCommandLabels
{
	PublicLabel CommandLabel = "CameraSet";
	PublicLabel NearLabel = "Near";
	PublicLabel FarLabel = "Far";
	PublicLabel EyePositionLabel = "EyePosition";
	PublicLabel TargetPositionLabel = "TargetPosition";
	PublicLabel UpVector = "UpVector";
}

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraSetCommand::Args::Args() :
	near(CameraSetCommandLabels::NearLabel, 0.1),
	far(CameraSetCommandLabels::FarLabel, 1.0),
	eyePosition(CameraSetCommandLabels::EyePositionLabel, Vector3dd(0, 0, 1)),
	targetPosition(CameraSetCommandLabels::TargetPositionLabel, Vector3dd(0,0,0)),
	upVector(CameraSetCommandLabels::UpVector, Vector3dd(0,1,0))
{
	add(&near);
	add(&far);
	add(&eyePosition);
	add(&targetPosition);
	add(&upVector);
}

std::string CameraSetCommand::getName()
{
	return CameraSetCommandLabels::CommandLabel;
}

bool CameraSetCommand::execute(World* world)
{
	auto camera = world->getCamera()->getCamera();
	camera->setNear( std::any_cast<float>(args.near) );
	camera->setFar( std::any_cast<float>(args.far) );
	//camera->setTarget(  );
	//camera->setUp()
	const auto& eyePosition = std::any_cast<Vector3dd>(args.eyePosition);
	const auto& targetPosition = std::any_cast<Vector3dd>(args.targetPosition);
	const auto& upVector = std::any_cast<Vector3dd>(args.upVector);
	camera->lookAt(eyePosition, targetPosition, upVector);
	return true;
}