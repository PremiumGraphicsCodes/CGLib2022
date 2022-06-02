#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class SPHVolumeConvertCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> particleSystemId;
		Command::Arg<int> volumeId;

		Command::Arg<float> particleRadius;
		Command::Arg<float> cellLength;
		Command::Arg<bool> isIsotorpic;

		Args();
	};

	struct Results : Command::IResults
	{
//		Command::Result<int> newId;

		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	SPHVolumeConvertCommand();

	const SPHVolumeConvertCommand(const Args& args);

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}