#pragma once

#include "IWindow.h"
#include <string>
#include <vector>

namespace Crystal {
	namespace UI {

class FileOpenMenu : public IWindow
{
public:
	explicit FileOpenMenu(const std::string& name);

	void addFilter(char const* filter);

	void onShow() override;

	std::string getFileName() const;

private:
	std::vector< char const* > filters;
	char const* filename;
};

	}
}