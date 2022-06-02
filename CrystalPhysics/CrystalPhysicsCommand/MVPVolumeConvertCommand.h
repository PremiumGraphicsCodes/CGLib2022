#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class MVPVolumeConvertCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> volumeParticleSystemId;
		Command::Arg<int> massParticleSystemId;
		Command::Arg<int> triangleMeshId;

		Command::Arg<float> particleRadius;
		Command::Arg<float> threshold;

		Args();
	};

	struct Results : Command::IResults
	{
		//		Command::Result<int> newId;

		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	MVPVolumeConvertCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}