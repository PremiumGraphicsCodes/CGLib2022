#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class PresenterSetCommand : public ICommand
{
public:
	PresenterSetCommand() :
		ICommand(&args, nullptr)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< int > id;
		Arg< std::string > presenterName;
	};

	/*
	struct Results : IResults
	{
		Results();

		Result<int> newId;
	};
	*/

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	//Results results;
};

	}
}