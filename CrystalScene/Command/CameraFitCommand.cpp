#include "CameraFitCommand.h"

#include "PublicLabel.h"

namespace CameraFitCommandLabels
{
	PublicLabel CameraFitCommandLabel = "CameraFit";
	PublicLabel CameraXYCommandLabel = "CameraXY";
	PublicLabel CameraYZCommandLabel = "CameraYZ";
	PublicLabel CameraZXCommandLabel = "CameraZX";
}

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string CameraFitCommand::getName()
{
	return CameraFitCommandLabels::CameraFitCommandLabel;
}

bool CameraFitCommand::execute(World* world)
{
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getCamera()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(0, 0, dist * 0.5), boundingBox.getCenter(), Vector3dd(0,1,0));
	//world->getCamera()->getPresenter()->updateView();
	return true;
}

std::string CameraXYCommand::getName()
{
	return CameraFitCommandLabels::CameraXYCommandLabel;
}

bool CameraXYCommand::execute(World* world)
{
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getCamera()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0), boundingBox.getCenter(), Vector3dd(0, 1, 0));
	//world->getCamera()->getPresenter()->updateView();
	return true;
}

std::string CameraYZCommand::getName()
{
	return CameraFitCommandLabels::CameraYZCommandLabel;
}

bool CameraYZCommand::execute(World* world)
{
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getCamera()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(dist * 2.0, 0, 0), boundingBox.getCenter(), Vector3dd(0, 0, 1));
	//world->getCamera()->getPresenter()->updateView();
	return true;
}

std::string CameraZXCommand::getName()
{
	return CameraFitCommandLabels::CameraZXCommandLabel;
}

bool CameraZXCommand::execute(World* world)
{
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getCamera()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(0, dist * 2.0, 0), boundingBox.getCenter(), Vector3dd(1, 0, 0));
	//world->getCamera()->getPresenter()->updateView();
	return true;
}
