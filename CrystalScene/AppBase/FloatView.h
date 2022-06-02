#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class FloatView : public IWindow
{
public:
	explicit FloatView(const std::string& name) :
		FloatView(name, 0.0f)
	{}

	FloatView(const std::string& name, const float value) :
		IWindow(name),
		value(value)
	{}

	void onShow() override;

	float getValue() const { return value; }

	void setValue(const float value) { this->value = value; }

private:
	float value;
};

	}
}