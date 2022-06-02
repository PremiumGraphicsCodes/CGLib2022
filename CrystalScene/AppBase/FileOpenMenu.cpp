#pragma once

#include "FileOpenMenu.h"

#include "tinyfiledialogs.h"

using namespace Crystal::UI;

FileOpenMenu::FileOpenMenu(const std::string& name) :
	IWindow(name),
	filename(nullptr)
{}

void FileOpenMenu::addFilter(char const* filter)
{
	filters.push_back(filter);
}

void FileOpenMenu::onShow()
{
	//char const * lFilterPatterns[2] = { "*.stl", "*.obj" };
	const auto filerCount = static_cast<int>(filters.size());
	filename = tinyfd_openFileDialog("Open", "", filerCount, filters.data(), nullptr, 0);
}

std::string FileOpenMenu::getFileName() const
{
	if (filename == nullptr) {
		return "";
	}
	return filename;
}
