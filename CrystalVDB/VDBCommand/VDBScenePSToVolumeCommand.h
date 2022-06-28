#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBScenePSToVolumeCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> sceneId;
		Command::Arg<double> radius;
		Command::Arg<double> voxelSize;
		Command::Arg<bool> isFlame;
		Command::Arg<float> flameTemperature;
		Command::Arg<float> smokeTemperature;
	};

	struct Results : Command::IResults
	{
		Results();

		Command::Arg<int> newSceneId;
	};

	VDBScenePSToVolumeCommand();

	explicit VDBScenePSToVolumeCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}