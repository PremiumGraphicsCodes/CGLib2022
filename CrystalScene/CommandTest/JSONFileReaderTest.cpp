#include "pch.h"
#include "gtest/gtest.h"

#include "../Command/JSONFileReader.h"
#include "../Command/MockCommand.h"
#include "../Command/FileImportCommand.h"

using namespace Crystal::Command;

TEST(JSONFileReaderTest, TestRead)
{
	JSONFileReader reader;
	CommandFactory factory;
	const auto isOk = reader.read("./TestFiles/test.json", factory);
	EXPECT_EQ(2, reader.getCommands().size());
	EXPECT_TRUE(isOk);
}