#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBSceneFileImportCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<std::string> filePath;
		Command::Arg<std::string> fileFormat;
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Result<int> newSceneId;

		//Command::Result<std::vector<int>> newIds;
	};

	VDBSceneFileImportCommand();

	explicit VDBSceneFileImportCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;

};

	}
}