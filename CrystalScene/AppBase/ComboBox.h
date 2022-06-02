#pragma once

#include "IWindow.h"

#include <map>
#include <functional>

namespace Crystal {
	namespace UI {

class ComboBox : public IWindow
{
public:
	explicit ComboBox(const std::string& name) :
		IWindow(name)
	{}

	void add(const std::string& label) { labelFuncMap[label] = std::function<void(void)>(); }

	void add(const std::string& label, const std::function<void(void)> func);

	void onShow() override;

	void setSelected(const std::string& label) { this->selectedLabel = label; }

	std::string getSelected() const;

private:
	std::map<std::string,std::function<void(void)>> labelFuncMap;
	std::string selectedLabel;
};
	}
}