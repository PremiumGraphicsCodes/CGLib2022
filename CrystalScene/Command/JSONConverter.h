#pragma once

#include <any>

#include "IArgs.h"
#include "ICommand.h"

#include "../ThirdParty/nlohmnn/json.hpp"

namespace Crystal {
	namespace Command {

class JSONConverter
{
public:
	static nlohmann::json toJSON(const std::any& value);

	static nlohmann::json toJSON(const IArgs& args);

	static nlohmann::json toJSON(const ICommand& command);

	static void fromJSON(const nlohmann::json& json, std::any& dest);

	static void fromJSON(const nlohmann::json& json, Arg<int>& dest);

	static void fromJSON(const nlohmann::json& json, ICommand& command);

private:
	//std::string toJsonText();
};
	}
}