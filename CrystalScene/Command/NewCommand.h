#pragma once

#include "../Command/ICommand.h"

namespace Crystal {
	namespace Command {

class NewCommand : public ICommand
{
public:
	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;
};
	}
}