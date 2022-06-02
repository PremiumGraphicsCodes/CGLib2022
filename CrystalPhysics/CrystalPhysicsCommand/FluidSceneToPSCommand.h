#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class FluidSceneToPSCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> fluidId;
		Command::Arg<int> particleSystemId;

		Args();
	};

	struct Results : Command::IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	FluidSceneToPSCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}