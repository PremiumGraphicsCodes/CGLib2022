#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class LightGetCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> id;
	};

	struct Results : IResults
	{
		Results();

		Result<Math::Vector3dd> position;
		Result<Graphics::ColorRGBAf> ambient;
		Result<Graphics::ColorRGBAf> diffuse;
		Result<Graphics::ColorRGBAf> specular;
		Result<std::string> name;
	};

	LightGetCommand() :
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