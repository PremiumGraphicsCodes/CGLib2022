#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class MeshBoundarySceneUpdateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> id;
		Command::Arg<int> meshId;
		Command::Arg<std::string> name;

		Args();
	};

	struct Results : Command::IResults
	{

		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	MeshBoundarySceneUpdateCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}