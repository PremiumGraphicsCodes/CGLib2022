#include "ScaleUICtrl.h"

#include "../Scene/World.h"

#include "../UI/Canvas.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

ScaleUICtrl::ScaleUICtrl(World* repository, Canvas* canvas) :
	repository(repository),
	canvas(canvas)
{
}

void ScaleUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void ScaleUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void ScaleUICtrl::onLeftDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;

	for (auto o : this->objects) {
		const double scalex = 1.0 + diff.x;
		const double scaley = 1.0 + diff.y;
		//o->(glm::vec3(diff.x, diff.y, 0.0));

		Matrix3dd matrix(
			scalex, 0.0, 0.0,
			0.0, scaley, 0.0,
			0.0, 0.0, 1.0
		);
		o->transform(matrix);
	}
	this->prevPosition = position;
	repository->updateViewModel();
}

void ScaleUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void ScaleUICtrl::onRightButtonUp(const Vector2df& position)
{

}