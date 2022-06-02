#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class MockCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Arg<int> lhs;
		Arg<int> rhs;

		Args() :
			lhs("lhs", 0),
			rhs("rhs", 0)
		{
			add(&lhs);
			add(&rhs);
		}
	};

	struct Results : IResults
	{
		Result<int> value;

		Results() :
			value("value", 0)
		{
			add(&value);
		}
	};

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	MockCommand() :
		ICommand(&args, &results)
	{}

	bool execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};
	}
}