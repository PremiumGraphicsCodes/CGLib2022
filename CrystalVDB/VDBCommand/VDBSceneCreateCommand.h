#pragma once

#include "CrystalScene/Command/ICommand.h"
#include <vector>

namespace Crystal {
	namespace VDB {

class VDBSceneCreateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<std::string> sceneType;
		Command::Arg<std::string> name;
		Command::Arg<std::vector<Math::Vector3dd>> positions;
		
		Args();
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Result<int> newId;
	};

	VDBSceneCreateCommand() :
		Command::ICommand(&args, &results)
	{}

	explicit VDBSceneCreateCommand(const Args& args) :
		args(args),
		Command::ICommand(&this->args, &results)
	{
	}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

	const Results& getResults() const { return results; }

private:
	Args args;
	Results results;
};

	}
}