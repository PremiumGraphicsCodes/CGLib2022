#pragma once

#include "ICommand.h"
#include <filesystem>

namespace Crystal {
	namespace Command {

class TXTFileImportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< int > id;
		Arg< std::string > filePath;
	};

	struct Results : IResults
	{
		Results();
	};

	TXTFileImportCommand() :
		ICommand(&args, &results)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* scene) override;

private:
	Args args;
	Results results;
};

	}
}