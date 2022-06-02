#pragma once

#include "IArgs.h"
#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraTranslateCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< Math::Vector3dd > translate;
	};

	CameraTranslateCommand() :
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