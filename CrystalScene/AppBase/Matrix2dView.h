#pragma once

#include "IWindow.h"

#include "../../Crystal/Math/Matrix2d.h"

namespace Crystal {
	namespace UI {

class Matrix2dView : public IWindow
{
public:
	explicit Matrix2dView(const std::string& name) :
		IWindow(name),
		value(Math::Matrix2dd(1, 0, 0, 1))
	{}

	Matrix2dView(const std::string& name, const Math::Matrix2dd& value) :
		IWindow(name),
		value(value)
	{}

	void onShow() override;

	void setValue(const Math::Matrix2dd& value) { this->value = value; }

	Math::Matrix2dd getValue() const { return value; }

private:
	Math::Matrix2dd value;
};

	}
}