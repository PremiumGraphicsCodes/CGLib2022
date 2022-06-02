#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class FluidSceneUpdateCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> id;
		Command::Arg<int> particleSystemId;
		Command::Arg<float> particleRadius;
		Command::Arg<float> density;
		Command::Arg<float> stiffness;
		Command::Arg<float> viscosity;
		Command::Arg<float> temperature;
		Command::Arg<float> heatDiffuseCoe;
		Command::Arg<float> dragForceCoe;
		Command::Arg<float> dragHeatCoe;
		Command::Arg<int> lifeLimit;

		Command::Arg<bool> isBoundary;
		Command::Arg<std::string> name;

		Args();
	};

	struct Results : Command::IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	FluidSceneUpdateCommand();

	explicit FluidSceneUpdateCommand(const Args& args);

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}