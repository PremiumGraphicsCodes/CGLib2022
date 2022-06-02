#include "FileSaveMenu.h"

#include "tinyfiledialogs.h"

using namespace Crystal::UI;

FileSaveMenu::FileSaveMenu(const std::string& name) :
	IWindow(name),
	filename(nullptr)
{}

void FileSaveMenu::addFilter(char const* filter)
{
	filters.push_back(filter);
}

void FileSaveMenu::onShow()
{
	const auto filterCount = static_cast<int>(filters.size());
	filename = tinyfd_saveFileDialog("Save", "", filterCount, filters.data(), nullptr);
}

std::string FileSaveMenu::getFileName() const
{
	if (filename == nullptr) {
		return "";
	}
	return filename;
}
