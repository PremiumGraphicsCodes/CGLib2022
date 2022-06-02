#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBSceneCompositeCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> sceneId1;
		Command::Arg<int> sceneId2;
		Command::Arg<std::string> compositeType;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBSceneCompositeCommand();

	explicit VDBSceneCompositeCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}