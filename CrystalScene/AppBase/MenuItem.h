#pragma once

#include "IMenuItem.h"
#include <functional>

namespace Crystal {
	namespace UI {

class MenuItem : public IMenuItem
{
public:
	explicit MenuItem(const std::string& name) :
		IMenuItem(name)
	{}

	MenuItem(const std::string& name, std::function<void()> func) :
		IMenuItem(name),
		func(func)
	{}

	~MenuItem()
	{}

	void setFunction(std::function<void(void)> func) {
		this->func = std::move(func);
	}

protected:
	void onPushed() override {
		this->func();
	}

private:
	std::function<void(void)> func;
};

	}

}