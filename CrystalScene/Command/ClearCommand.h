#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class ClearCommand : public ICommand
{
public:
	struct Args : public IArgs
	{
		Args();
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	ClearCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
};
	}
}