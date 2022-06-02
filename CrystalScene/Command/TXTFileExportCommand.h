#pragma once

#include "ICommand.h"
//#include <filesystem>

namespace Crystal {
	namespace Command {

class TXTFileExportCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg< std::vector<int> > ids;
		Arg< std::string > filePath;
	};

	struct Results : IResults
	{
		Results();
	};

	TXTFileExportCommand() :
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