#pragma once

#include "CrystalScene/Command/ICommand.h"
#include "Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Physics {

class FluidVolumeExportCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Command::Arg<int> volumeId;
		Command::Arg<std::string> filePath;

		Args();
	};

	struct Results : Command::IResults
	{
		Results();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	FluidVolumeExportCommand();

	explicit FluidVolumeExportCommand(const Args& args);

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}