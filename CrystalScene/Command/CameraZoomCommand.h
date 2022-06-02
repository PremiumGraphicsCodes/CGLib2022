#pragma once

#include "IArgs.h"
#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraZoomCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< float > ratio;
	};

	CameraZoomCommand() :
		ICommand(&args)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
};

	}
}