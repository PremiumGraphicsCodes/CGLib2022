#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraFitCommand : public ICommand
{
public:
	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;
};

class CameraXYCommand : public ICommand
{
public:
	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;
};

class CameraYZCommand : public ICommand
{
public:
	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;
};

class CameraZXCommand : public ICommand
{
public:
	static std::string getName();

	std::string getCommandName() const { return getName(); }

	bool execute(Scene::World* world) override;
};


	}
}