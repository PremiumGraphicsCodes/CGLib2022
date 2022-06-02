#pragma once

#include "Crystal/Util/UnCopyable.h"
#include "IArgs.h"
#include "IResults.h"

#include "../Scene/World.h"

namespace Crystal {
	namespace Command {

class ICommand : private UnCopyable
{
public:
	ICommand() :
		args(nullptr),
		results(nullptr)
	{}

	explicit ICommand(IArgs* args) :
		args(args),
		results(nullptr)
	{}

	ICommand(IArgs* args, IResults* results) :
		args(args),
		results(results)
	{}

	virtual ~ICommand(){}

	void setArg(const std::string& name, std::any value) { args->setValue(name, value); }

	const std::type_info& getArgType(const std::string& name) { return args->getType(name); }

	virtual std::string getCommandName() const = 0;

	virtual bool execute(Scene::World* scene) = 0;

	std::any getResult(const std::string& name) { return results->getValue(name); }

	//void writeJSON(const std::string& filePath);

	//void readJSON(const std::string& filePath);

	const IArgs* getArgs() const { return args; }

private:
	IArgs* args;
	IResults* results;
};
	}
}