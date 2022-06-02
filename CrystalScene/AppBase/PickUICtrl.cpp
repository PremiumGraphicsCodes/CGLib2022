#include "PickUICtrl.h"

#include "../Scene/World.h"
#include "../Command/Command.h"
#include "../Command/PickCommand.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PickUICtrl::PickUICtrl(World* model, Canvas* canvas, const SceneType& type, const float mergin) :
	model(model),
	canvas(canvas),
	type(type),
	mergin(mergin)
{
	function = [](int parentId, int childId) {
		;
	};
}

void PickUICtrl::onLeftButtonDown(const Vector2df& position)
{
	const auto x = position.x;
	const auto y = position.y;

	//std::cout << x << " " << y << std::endl;
	const auto dx = mergin / canvas->getWidth();
	const auto dy = mergin / canvas->getHeight();
	for (float x = -mergin; x < mergin; x += dx) {
		for (float y = -mergin; y < mergin; y += dy) {
			/*
			Crystal::Command::Command command(PickLabels::PickCommandLabel);
			command.setArg(PickLabels::PositionLabel, Vector2dd(position));
			command.execute(model);
			const auto parentId = std::any_cast<int>(command.getResult(PickLabels::ParentIdLabel));

			if (parentId == 0) {
				continue;
			}

			const auto childId = std::any_cast<int>(command.getResult(PickLabels::ChildIdLabel));

			auto object = model->getScenes()->findSceneById(parentId);
			if (object != nullptr) {
				const bool masked = (type == object->getType());
				if (masked) {
					function(parentId, childId);
					return;
				}
			}
			*/
		}
	}
}

void PickUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void PickUICtrl::onLeftDragging(const Vector2df& position)
{
}

void PickUICtrl::onRightButtonDown(const Vector2df& position)
{
}

void PickUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void PickUICtrl::onRightDragging(const Vector2df& position)
{
}

void PickUICtrl::onWheel(const float dx)
{
	//camera->zoom(dx);
}
