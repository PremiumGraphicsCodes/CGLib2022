#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class EmitterSceneUpdateCommand : public Command::ICommand
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
		Command::Arg<Math::Vector3df> initialVelocity;
		Command::Arg<std::string> name;

		Command::Arg<int> startStep;
		Command::Arg<int> endStep;
		Command::Arg<int> interval;

		Command::Arg<float> temperature;
		Command::Arg<float> heatDiffuseCoe;
		Command::Arg<float> dragForceCoe;
		Command::Arg<float> dragHeatCoe;
		Command::Arg<int> lifeLimit;

		Args();
	};

	struct Results : Command::IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	EmitterSceneUpdateCommand();

	explicit EmitterSceneUpdateCommand(const Args& args);

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}