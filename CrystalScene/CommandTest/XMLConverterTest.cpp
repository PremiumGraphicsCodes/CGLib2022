#include "pch.h"
#include "gtest/gtest.h"

#include "Crystal/Math/Vector3d.h"
#include "../Command/XMLConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(XMLConverterTest, TestVector3dds)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root = doc.NewElement("Root");
	doc.InsertEndChild(root);

	auto e = XMLConverter::toXML(&doc, "Vector3dd", Vector3dd(1,2,3));
	root->InsertEndChild(e);

	Vector3dd dest;
	XMLConverter::fromXML(*root, "Vector3dd", dest);
	EXPECT_EQ(dest.x, 1);
	EXPECT_EQ(dest.y, 2);
	EXPECT_EQ(dest.z, 3);
	//doc.Print(&printer);
	//std::cout << doc.ToText() << std::endl;
}
