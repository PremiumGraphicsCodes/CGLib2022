#pragma once

#include "IView.h"
#include "Button.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class DirectoryView : public IView
{
public:
	explicit DirectoryView(const std::string& name);

	DirectoryView(const std::string& name, const std::string& path);

	std::string getPath() const { return pathView.getValue(); }

private:
	void onSelect();

private:
	Button selectButton;
	StringView pathView;
};

	}
}