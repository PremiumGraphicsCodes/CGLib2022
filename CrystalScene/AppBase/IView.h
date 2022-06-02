#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class IView : public IWindow
{
public:
	explicit IView(const std::string& name) :
		IWindow(name)
	{}

	virtual ~IView() {};

	void onShow() override {
		for (auto c : children) {
			c->show();
		}
	}
};

	}
}