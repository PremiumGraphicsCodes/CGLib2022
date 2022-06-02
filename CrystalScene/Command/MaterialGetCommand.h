#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class MaterialGetCommand : public ICommand
{
public:
	struct Args : public IArgs
	{
		Args();

		Arg<int> id;
	};

	struct Results : public IResults
	{
		Results();

		Result<Graphics::ColorRGBAf> ambient;
		Result<Graphics::ColorRGBAf> diffuse;
		Result<Graphics::ColorRGBAf> specular;
		Result<float> shininess;
//		Result<std::string> textureName;
		Result<std::string> name;
	};

	MaterialGetCommand() :
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