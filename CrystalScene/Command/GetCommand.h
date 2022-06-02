#pragma once

#include <string>
#include <any>
#include "../Scene/World.h"

namespace Crystal {
	namespace Command {

class GetCommand
{
public:
	static std::any Get(Scene::World* world, const std::string& name);

	static std::any Get(Scene::World* world, int id, const std::string& name);
};

	}
}