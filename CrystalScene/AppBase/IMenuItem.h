#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class IMenuItem : public IWindow
{
public:
	explicit IMenuItem(const std::string& name) :
		IWindow(name)
	{}

	virtual ~IMenuItem()
	{}

	void onShow() override;

protected:
	virtual void onPushed() = 0;

private:
};
	}
}