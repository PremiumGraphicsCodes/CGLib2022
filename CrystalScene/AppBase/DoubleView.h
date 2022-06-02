#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class DoubleView : public IWindow
{
public:
	explicit DoubleView(const std::string& name);

	DoubleView(const std::string& name, const double value);

	void onShow() override;

	double getValue() const { return value; }

	void setValue(const double value) { this->value = value; }

private:
	double value;
};

	}
}