#include "pch.h"
#include "gtest/gtest.h"

#include "../Command/JSONFileWriter.h"
#include "../Command/MockCommand.h"
#include "../Command/FileImportCommand.h"

using namespace Crystal::Command;

TEST(JSONFileWriterTest, TestWrite)
{
	MockCommand command;
	FileImportCommand command2;
	JSONFileWriter writer;
	writer.add(&command);
	writer.add(&command2);
	const auto isOk = writer.write("./TestFiles/test.json");
	EXPECT_TRUE(isOk);
}