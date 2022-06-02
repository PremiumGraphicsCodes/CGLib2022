#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class MaterialSetCommand : public ICommand
{
public:
	struct Args : IArgs
	{
		Args();

		Arg<int> id;
		Arg<Graphics::ColorRGBAf> ambient;
		Arg<Graphics::ColorRGBAf> diffuse;
		Arg<Graphics::ColorRGBAf> specular;
		Arg<float> shininess;
//		Arg<std::string> textureName;
		Arg<std::string> name;
	};

	MaterialSetCommand() :
		ICommand(&args, nullptr)
	{}

	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;

private:
	Args args;
};

	}
}