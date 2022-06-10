#include "pch.h"
#include "gtest/gtest.h"

#include "../Command/XMLFileWriter.h"

using namespace Crystal::Command;

TEST(XMLFileWriterTest, TestWrite)
{
	Property<int> intValue("Int", 1);
	Property<double> doubleValue("Double", 3.14);
	PropertyTree tree1("Tree");
	tree1.add(&intValue);
	tree1.add(&doubleValue);

	Property<float> floatValue("Float", 3.14f);
	Property<std::string> textValue("Text", "Hello");
	PropertyTree tree2("Tree2");
	tree2.add(&floatValue);
	tree2.add(&textValue);
	Property<std::string> name("Name", "AAA");
	tree1.addAttribute(&name);
	tree1.add(&tree2);

	XMLFileWriter writer;
	const auto isOk = writer.write(tree1, "./TestFiles/test.xml");
	EXPECT_TRUE(isOk);
}