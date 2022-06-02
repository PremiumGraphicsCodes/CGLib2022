#include "MoveUICtrl.h"

#include "../Scene/World.h"

#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MoveUICtrl::MoveUICtrl(World* repository, Canvas* canvas) :
	repository(repository),
	canvas(canvas)
{
}

void MoveUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
	//	camera->move();
}

void MoveUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void MoveUICtrl::onLeftDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;

	/*
	auto& os = repository->getObjects()->getFactory()->getPolygonMeshes();
	for (auto o : os) {
		o->move(glm::vec3(diff.x, diff.y, 0.0));
	}
	this->prevPosition = position;
	canvas->setViewModel(repository->toViewModel());
	*/
}

void MoveUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void MoveUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void MoveUICtrl::onRightDragging(const Vector2df& position)
{
	const auto& diff = prevPosition - position;
	const auto& rotation = rotationMatrixX(diff.x) * rotationMatrixY(diff.y);

	for (auto o : objects) {
		o->transform(rotation);
	}
	this->prevPosition = position;
	//canvas->setViewModel(repository->toViewModel());
	repository->updateViewModel();
}

void MoveUICtrl::onMiddleButtonDown(const Vector2df& position)
{

}

void MoveUICtrl::onMiddleButtonUp(const Vector2df& position)
{

}

void MoveUICtrl::onMiddleDragging(const Vector2df& position)
{

}


void MoveUICtrl::onWheel(const float dx)
{
	//camera->zoom(dx / 100.0f);
}
