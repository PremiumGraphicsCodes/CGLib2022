#pragma once

#include "CrystalScene/Command/ICommand.h"

namespace Crystal {
	namespace VDB {

class VDBSceneTransformCommand : public Command::ICommand
{
public:
	struct Args : Command::IArgs
	{
		Args();

		Command::Arg<int> vdbSceneId;
		Command::Arg<Math::Matrix4dd> matrix;
	};

	struct Results : Command::IResults
	{
		Results();
	};

	VDBSceneTransformCommand();

	explicit VDBSceneTransformCommand(const Args& args);

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}