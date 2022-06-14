#pragma once

#include "Property.h"

namespace Crystal {
	namespace Command {

struct PropertyTree
{
	PropertyTree()
	{}

	explicit PropertyTree(const std::string& name) :
		name(name)
	{}

	void setName(const std::string& name) {
		this->name = name;
	}

	std::string getName() const { return name; }

	void add(IProperty* arg) { values.push_back(arg); }

	void add(PropertyTree* child) { children.push_back(child); }

	void addAttribute(IProperty* attr) { attributes.push_back(attr); }

	std::any getValue(const std::string& name) const {
		auto iter = std::find_if(values.begin(), values.end(), [=](auto a) { return a->name == name; });
		return (*iter)->value;
	};

	void setValue(const std::string& name, const std::any& value) {
		auto iter = std::find_if(values.begin(), values.end(), [=](auto a) { return a->name == name; });
		(*iter)->value = value;
	}

	const std::type_info& getType(const std::string& name) const {
		return getValue(name).type();
	}

	std::vector<IProperty*> getValues() const { return values; }

	std::vector<PropertyTree*> getChildren() const { return children; }

	std::vector<IProperty*> getAttributes() const { return attributes; }


	PropertyTree* getChild(const std::string& name) const {
		auto iter = std::find_if(children.begin(), children.end(), [=](auto a) { return a->name == name; });
		return (*iter);
	}

	std::vector<PropertyTree*> getChildren(const std::string& name) const {
		std::vector<PropertyTree*> results;
		for (const auto& c : children) {
			if (c->name == name) {
				results.push_back(c);
			}
		}
		return results;
	}
	/*

	void setValue(const std::string& name, std::any value) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		(*iter)->value = value;
	}
	*/

private:
	std::string name;
	std::vector<IProperty*> values;
	std::vector<IProperty*> attributes;
	std::vector<PropertyTree*> children;
};

	}
}