#include "CameraScene.h"

#include "Crystal/Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

CameraScene::CameraScene(const int id, const std::string& name, Camera* camera) :
	IScene(id, name),
	camera(camera)
{
}


/*
void CameraScene::fitCamera(const Box3d& boundingBox)
{
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->setTarget(boundingBox.getCenter());
	camera->moveTo(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0));
}

void CameraScene::setCameraXY(const Box3d& boundingBox)
{
	fitCamera(boundingBox);
	camera->setRotation(glm::mat4());
}

void CameraScene::setCameraYZ(const Box3d& boundingBox)
{
	fitCamera(boundingBox);
	camera->rotate(glm::radians(90.0f), 0.0);
}

void CameraScene::setCameraZX(const Box3d& boundingBox)
{
	fitCamera(boundingBox);
	camera->rotate(0.0, glm::radians(90.0f));
}

*/