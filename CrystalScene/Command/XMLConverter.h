#pragma once

#include <any>
#include "tinyxml2.h"
#include "PropertyTree.h"
#include <memory>

namespace Crystal {
	namespace Command {

class XMLConverter
{
public:
	template<typename T>
	static tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, const std::string& name, const T value);
	
	static tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, const std::string& name, const std::any& value);

	static tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, const PropertyTree& tree);

	//static nlohmann::json toJSON(const ICommand& command);

	template<typename T>
	static void fromXML(const tinyxml2::XMLElement& text, const std::string& name, T& value);

	template<typename T>
	static T fromXML(const tinyxml2::XMLElement& text, const std::string& name);

	static void fromXML(const tinyxml2::XMLElement& text, std::any& dest);

	static bool fromXML(const tinyxml2::XMLElement& parent, PropertyTree& tree);

	//static void fromJSON(const nlohmann::json& json, ICommand& command);

};
	}
}