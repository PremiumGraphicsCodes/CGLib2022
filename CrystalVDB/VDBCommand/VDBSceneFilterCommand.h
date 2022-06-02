#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBSceneFilterCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> vdbSceneId;
		Command::Arg<int> width;
		Command::Arg<int> iteration;
		Command::Arg<std::string> filterType;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBSceneFilterCommand();

	explicit VDBSceneFilterCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}