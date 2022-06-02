#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraCreateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();
	};

	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};

	CameraCreateCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

	}
}