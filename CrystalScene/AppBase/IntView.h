#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class IntView : public IWindow
{
public:
	explicit IntView(const std::string& name) :
		IWindow(name),
		value(0)
	{}

	IntView(const std::string& name, const int value) :
		IWindow(name),
		value(value)
	{}

	void onShow() override;

	int getValue() const { return value; }

	void setValue(const int value) { this->value = value; }

private:
	int value;
};

	}
}