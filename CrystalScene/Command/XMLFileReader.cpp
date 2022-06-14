#include "XMLFileReader.h"
#include "tinyxml2.h"

#include "XMLConverter.h"

using namespace Crystal::Command;

bool XMLFileReader::read(const std::filesystem::path& path)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.LoadFile(path.string().c_str());
	if (ret != 0) {
		//fprintf(stderr, "fail to load xml file: %s\n", file_name);
		return false;
	}

	auto root = doc.RootElement();

	this->tree = std::make_unique<PropertyTree>();
	read(root, *this->tree);

	return true;
}

bool XMLFileReader::read(tinyxml2::XMLElement* parent, PropertyTree& tree)
{
	auto a = parent->FirstAttribute();
	while (a != nullptr) {
		a->Name();
		a->Value();
		a = a->Next();
	}

	auto c = parent->FirstChildElement();

	while (c != nullptr) {
		const std::string name = c->Value();
		const auto text = c->GetText();

		if (text == nullptr) {
			PropertyTree* t = new PropertyTree(name);
			read(c, *t);
			tree.add(t);
		}
		else {
			tree.add(new Property<std::string>(name, text));
		}
		c = c->NextSiblingElement();
	}

	return true;
}