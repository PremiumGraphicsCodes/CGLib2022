#include "pch.h"

#include "../VDBCommand/VDBCommandFactory.h"
#include "../VDBCommand/VDBInitCommand.h"


TEST(VDBRunnerTest, TestInitCommand)
{
	const std::string filepath("./TestFiles/init.json");

	VDBInitCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}
