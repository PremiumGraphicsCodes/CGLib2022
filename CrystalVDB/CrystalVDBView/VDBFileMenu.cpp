#include "VDBFileMenu.h"

#include "../CrystalVDB/VDBFileReader.h"
#include "../CrystalVDB/VDBFileWriter.h"
#include "../CrystalVDB/VDBPointsScene.h"

#include "CrystalScene/AppBase/FileOpenMenu.h"
#include "CrystalScene/AppBase/FileSaveMenu.h"

#include "../VDBCommand/VDBSceneFileImportCommand.h"
//#include "../VDBCommand/PublicLabels/VDBFileReadLabels.h"
#include "CrystalScene/AppBase/MenuItem.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VDBFileMenu::VDBFileMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas)
{
	add(new MenuItem("Import", [&] { onImport(); }));
	add(new MenuItem("Export", [&] { onExport(); }));
}

void VDBFileMenu::onImport()
{
	FileOpenMenu view("");
	view.addFilter("*.vdb");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
		/*
		VDBFileReader reader;
		const auto isOk = reader.open(filename);
		if (isOk) {
			VDBFileReadCommand::Args args;
			args.filePath.setValue(filename);
			VDBFileReadCommand command(args);
			const auto isOk = command.execute(getWorld());
			if (isOk) {
				const auto results = command.getResults();
				const auto newIds = std::any_cast<std::vector<int>>(results.newIds.value);
				for (const auto& id : newIds) {
					auto ps = getWorld()->getScenes()->findSceneById(id);
					auto presenter = ps->getPresenter();
					presenter->createView(getWorld()->getRenderer());
				}
				std::cout << "import suceeded." << std::endl;
			}
			else {
				std::cout << "import failed." << std::endl;
			}
		}
		*/
	}
}

void VDBFileMenu::onExport()
{
	FileSaveMenu fileSaveView("Export");
	fileSaveView.addFilter("*.vdb");
	fileSaveView.show();
	const auto& filename = fileSaveView.getFileName();
	if (!filename.empty()) {
		VDBFileWriter writer;
		const auto isOk = writer.open(filename);
		if (isOk) {
			const auto pointType = SceneType(VDBPointsScene::Type);
			const auto pointScenes = getWorld()->getScenes()->findScenes(pointType);
			for (auto s : pointScenes) {
				auto ps = static_cast<VDBPointsScene*>(s);
				writer.writePoints("name", ps);
			}
			std::cout << "export succeded." << std::endl;
		}
		else {
			std::cout << "export failed." << std::endl;
		}
	}
}