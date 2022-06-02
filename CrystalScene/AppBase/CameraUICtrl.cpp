#include "CameraUICtrl.h"
#include "../Command/Command.h"
#include "../Command/CommandFactory.h"
#include "../Command/CameraTranslateCommand.h"
#include "../Command/CameraRotateCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Command;

CameraUICtrl::CameraUICtrl(World* world) :
	prevPosition(0.0f,0.0f),
	world(world)
{
}

void CameraUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
//	camera->move();
}

void CameraUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void CameraUICtrl::onLeftDragging(const Vector2df& position)
{
	auto camera = world->getCamera()->getCamera();

	const auto diff = prevPosition - position;
	const auto bb = world->getBoundingBox();
	const auto scale = glm::distance(bb.getMin(), bb.getMax()) * 0.1;

	const auto& matrix = camera->getRotationMatrix();
	const auto v = glm::transpose( Matrix3dd( matrix ) ) * Vector3dd( diff, 0.0);

	auto command = CameraTranslateCommand();
	Math::Vector3dd t(v.x * scale, v.y * scale, v.z*scale);
	command.setArg("Translate", t);
	command.execute(world);

	this->prevPosition = position;
}

void CameraUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void CameraUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void CameraUICtrl::onRightDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;
	auto command = CameraRotateCommand();
	const auto& matrix = world->getCamera()->getCamera()->getRotationMatrix();
	const auto v = glm::transpose(Matrix3dd(matrix)) * Vector3dd(diff.y, diff.x, 0.0);
	const auto matrix1 = rotationMatrixX(v.x);
	const auto matrix2 = rotationMatrixY(v.y);
	const auto matrix3 = rotationMatrixZ(v.z);
	command.setArg("Matrix", matrix3 * matrix2 * matrix1);
	command.execute(world);
	//camera->rotate(diff.y, diff.x);
	this->prevPosition = position;
}

void CameraUICtrl::onWheel(const float dx)
{
	const auto bs = world->getBoundingBox();
	const auto length = (float)glm::distance(bs.getMin(), bs.getMax()) * 0.1f;
	const auto camera = world->getCamera()->getCamera();
	const auto f = camera->getForward();
	camera->setEye(camera->getEye() + f * dx * length);
	camera->setTarget(camera->getTarget() + f * dx * length);
	//world->getCamera()->getCamera()->zoom(dx / 100.0f);
}
