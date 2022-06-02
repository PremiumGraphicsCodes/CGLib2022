#pragma once

#include <string>
#include <any>
#include <vector>
#include <algorithm>

namespace Crystal {
	namespace Command {

struct IProperty
{
	IProperty()
	{}

	IProperty(const std::string& name, std::any value) :
		name(name),
		value(value)
	{}

	std::string name;
	std::any value;
};

template<typename T>
struct Property : public IProperty
{
	Property(const std::string& name, T value) :
		IProperty(name, value)
	{}

	T getValue() { return std::any_cast<T>(value); }

	void setValue(const T value) { this->value = value; }
};

	}
}