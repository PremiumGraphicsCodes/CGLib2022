#pragma once

#include "IWindow.h"

#include "imgui.h"

#include "../../Crystal/Math/Vector2d.h"

namespace Crystal {
	namespace UI {

class Vector2dView : public IWindow
{
public:
	explicit Vector2dView(const std::string& name) :
		IWindow(name),
		value(0,0)
	{}

	Vector2dView(const std::string& name, const Math::Vector2dd& value) :
		IWindow(name),
		value(value)
	{}

	void onShow() override {
		ImGui::InputFloat2(name.c_str(), &value[0]);
	}

	void setValue(const Math::Vector2dd& value) { this->value = value; }

	Math::Vector2dd getValue() const { return value; }

private:
	Math::Vector2df value;
};

	}
}