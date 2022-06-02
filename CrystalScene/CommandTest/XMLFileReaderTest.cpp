#include "pch.h"
#include "gtest/gtest.h"

#include "../Command/XMLFileReader.h"

using namespace Crystal::Command;

namespace {

	class LBFactory : public IPropertyTreeFactory
	{
		PropertyTree* create(const std::string& name) const override
		{
			if (name == "Tree")
			{
				auto tree = new PropertyTree("Tree");
				tree->add( new Property<int>("Int", 1));
				tree->add( new Property<double>("Double", 3.14));
				return tree;
			}
			else if (name == "Tree2")
			{
				auto tree2 = new PropertyTree("Tree2");
				tree2->add( new Property<float>("Float", 3.14f));
				tree2->add(new Property<std::string>("Text", "Hello"));
				return tree2;
			}
			else {
				assert(false);
				return nullptr;
			}
		}
	};
}

TEST(XMLFileReaderTest, TestRead)
{
	LBFactory factory;

	XMLFileReader reader;
	const auto isOk = reader.read("./TestFiles/test.xml", factory);
	EXPECT_TRUE(isOk);
	EXPECT_EQ(1, reader.getTree()->getChildren().size());
}