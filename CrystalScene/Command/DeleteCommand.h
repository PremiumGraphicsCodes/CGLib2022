#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class DeleteCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> id;
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	DeleteCommand();

	bool execute(Scene::World* world) override;

private:
	Args args;
};
	}
}