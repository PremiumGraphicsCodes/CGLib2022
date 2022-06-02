#pragma once

#include <memory>
#include "../Scene/World.h"
#include "IUICtrl.h"

namespace Crystal {
	namespace UI {

class CameraUICtrl : public IUICtrl
{
public:
	explicit CameraUICtrl(Scene::World* world);

	virtual ~CameraUICtrl() {}

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override;

	virtual void onWheel(const float dx) override;

private:
	Math::Vector2df prevPosition;
	Scene::World* world;
};
	}
}