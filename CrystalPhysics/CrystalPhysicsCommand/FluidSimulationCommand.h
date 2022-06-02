#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class FluidSimulationCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> solverId;

		Args();
	};

	struct Results : Command::IResults
	{
		/*
		Command::Result<int> value;

		Results() :
			value("value", 0)
		{
			add(&value);
		}
		*/
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	FluidSimulationCommand() :
		ICommand(&args, &results)
	{}

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};
	}
}