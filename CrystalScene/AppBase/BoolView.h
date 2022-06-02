#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class BoolView : public IWindow
{
public:
	explicit BoolView(const std::string& name);

	BoolView(const std::string& name, const bool value);

	void onShow() override;

	bool getValue() const { return value; }

	void setValue(const bool value) { this->value = value; }

private:
	bool value;
};

	}
}