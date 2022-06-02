#include "FileMenu.h"
#include "tinyfiledialogs.h"
#include "Canvas.h"
#include "FileOpenMenu.h"
#include "FileSaveMenu.h"
#include "../Scene/World.h"
#include "../Command/CameraFitCommand.h"
#include "../Command/Command.h"
#include "../Command/FileImportCommand.h"
#include "../Command/FileExportCommand.h"
#include "../Command/NewCommand.h"
#include "MenuItem.h"

#include <iostream>

using namespace Crystal::UI;
using namespace Crystal::Command;

FileMenu::FileMenu(const std::string& name, Scene::World* model, Canvas* canvas) :
	IMenu(name, model, canvas)
{
	add(new MenuItem("New", [&] { onNew(); }));
	add(new MenuItem("Import", [&] { onImport(); }));
	add(new MenuItem("Export", [&] { onExport(); }));
	add(new MenuItem("SS", [&] {onSS(); }));
}

void FileMenu::onNew()
{
	NewCommand command;
	command.execute(getWorld());
}

void FileMenu::onImport()
{
	FileOpenMenu view("");
	view.addFilter("*.stl");
	view.addFilter("*.obj");
	view.addFilter("*.mtl");
	view.addFilter("*.pcd");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
		/*
		FileImportCommand command;
		command.setArg(Fil::FilePathLabel, std::string(filename));
		bool isOk = command.execute(model);
		if (!isOk) {
			std::cout << "import failed." << std::endl;
		}
		else {
			const int newId = std::any_cast<int>(command.getResult(FileImportLabels::NewIdLabel));
			auto scene = model->getScenes()->findSceneById<Crystal::Scene::IScene*>(newId);
			auto presenter = scene->getPresenter();
			presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
//					scene->getParent()->se
				}
				*/
	}
	//canvas->update();
}

void FileMenu::onExport()
{
	FileSaveMenu view("");
	view.addFilter("*.stl");
	view.addFilter("*.obj");
	view.addFilter("*.mtl");
	view.addFilter("*.pcd");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
		/*
		Crystal::Command::Command command(FileExportLabels::FileExportCommandLabel);
		command.setArg(FileExportLabels::FilePathLabel, filename);
		const auto isOk = command.execute(model);
		if (!isOk) {
			std::cout << "export failed." << std::endl;
		}
		*/
	}
	//model->write(filename);
}

void FileMenu::onSS()
{
	FileOpenMenu view("");
	view.addFilter("*.png");
	view.addFilter("*.bmp");
	view.show();
	const auto filename = view.getFileName();
	const auto& image = getCanvas()->getImage();
}