#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class ShaderBuildCommand : public ICommand
{
public:
	ShaderBuildCommand() :
		ICommand(&args, nullptr)
	{}

	struct Args : IArgs
	{
		Args();

		Arg< int > id;
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