#pragma once

#include <string>
#include <any>
#include <vector>
#include <algorithm>

#include "Property.h"

namespace Crystal {
	namespace Command {

using IArg = IProperty;

template<typename T>
struct Arg : IArg
{
	Arg(const std::string& name, T value) :
		IArg(name, value)
	{}

	T getValue() { return std::any_cast<T>(value); }

	void setValue(const T value) { this->value = value; }
};

struct IArgs
{
	void add(IArg* arg) { args.push_back(arg); }

	std::any getValue(const std::string& name) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		return (*iter)->value;
	};

	const std::type_info& getType(const std::string& name) {
		return getValue(name).type();
	}

	void setValue(const std::string& name, std::any value) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		(*iter)->value = value;
	}

	std::vector<IArg*> args;
};

	}
}