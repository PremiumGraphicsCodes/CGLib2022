#include "pch.h"
#include "gtest/gtest.h"

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Box3d.h"
#include "../Command/XMLConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(XMLConverterTest, TestVector3dd)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root = doc.NewElement("Root");
	doc.InsertEndChild(root);

	auto e = XMLConverter::toXML(&doc, "Vector3dd", Vector3dd(1,2,3));
	root->InsertEndChild(e);

	const auto dest = XMLConverter::fromXML<Vector3dd>(*root, "Vector3dd");
	EXPECT_EQ(dest.x, 1);
	EXPECT_EQ(dest.y, 2);
	EXPECT_EQ(dest.z, 3);
}

TEST(XMLConverterTest, TestBox3dd)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root = doc.NewElement("Root");
	doc.InsertEndChild(root);

	const Box3dd box(Vector3dd(1, 2, 3), Vector3dd(4, 5, 6));
	auto e = XMLConverter::toXML(&doc, "Box3dd", box);
	root->InsertEndChild(e);

	const auto dest = XMLConverter::fromXML<Box3dd>(*root, "Box3dd");
	EXPECT_EQ(dest.getMin(), box.getMin());
	EXPECT_EQ(dest.getMax(), box.getMax());
}
