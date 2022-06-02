#pragma once

#include "IArgs.h"
#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraRotateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< Math::Matrix3dd > matrix;
	};

	CameraRotateCommand() :
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