#include "pch.h"

#include "../Command/CommandFactory.h"

using namespace Crystal::Command;

TEST(CommandFactoryTest, TestCreate)
{
	auto actual = CommandFactory::create("Mock");
	EXPECT_NE(nullptr, actual);
}