#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class CheckBox : public IWindow
{
public:
	explicit CheckBox(const std::string& name);

	CheckBox(const std::string& name, const bool v);

	void onShow() override;

	void setValue(const bool v) { this->value = v; }

	bool getValue() const { return value; }

private:
	bool value;
};

	}
}