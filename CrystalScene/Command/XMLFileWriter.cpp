#include "XMLFileWriter.h"

#include "XMLFileWriter.h"
#include "XMLConverter.h"
#include <fstream>

#include "tinyxml2.h"

using namespace Crystal::Command;

bool XMLFileWriter::write(const PropertyTree& tree, const std::filesystem::path& path)
{
	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.Parse(declaration);
	if (ret != 0) {
		fprintf(stderr, "fail to parse xml file: %s\n", declaration);
		return false;
	}

	tinyxml2::XMLComment* comment = doc.NewComment("this is a xml test file");
	doc.InsertEndChild(comment);

	auto e = XMLConverter::toXML(&doc, tree);

	doc.InsertEndChild(e);

	//model->toXML(&doc, root);
	ret = doc.SaveFile(path.string().c_str());
	if (ret != 0) {
		return false;
	}

	return true;
}
