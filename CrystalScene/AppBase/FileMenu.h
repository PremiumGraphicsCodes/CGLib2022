#pragma once

#include "IMenu.h"

namespace Crystal {
	namespace UI {

class FileMenu : public IMenu
{
public:
	FileMenu(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onNew();

	void onImport();

	void onExport();

	void onSS();
};
	}
}