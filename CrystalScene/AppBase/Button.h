#pragma once

#include "IWindow.h"
#include <functional>

namespace Crystal {
	namespace UI {

class Button : public IWindow
{
public:
	explicit Button(const std::string& name) :
		IWindow(name)
	{}

	Button(const std::string& name, std::function<void()> func) :
		IWindow(name),
		func(func)
	{}

	~Button()
	{}

	void onShow() override;

	void setFunction(std::function<void(void)> func) {
		this->func = std::move(func);
	}

private:
	std::function<void(void)> func;
};
	}
}