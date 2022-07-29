#pragma once

#include "../../Crystal/Math/Vector2d.h"

namespace Crystal {
	namespace UI {

class IMouseListener
{
public:
	virtual void onLeftButtonDown(const Math::Vector2df& position) {};

	virtual void onLeftButtonUp(const Math::Vector2df& position) {};

	virtual void onRightButtonDown(const Math::Vector2df& position) {};

	virtual void onRightButtonUp(const Math::Vector2df& position) {};

	virtual void onMiddleButtonDown(const Math::Vector2df& position) {};

	virtual void onMiddleButtonUp(const Math::Vector2df& position) {};

	virtual void onLeftDragging(const Math::Vector2df& position) {};

	virtual void onRightDragging(const Math::Vector2df& position) {};

	virtual void onMiddleDragging(const Math::Vector2df& position) {};

	virtual void onWheel(const float dx) {};
};

	}
}