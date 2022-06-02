#include "pch.h"

#include "CrystalVDB/VDBCommand/VDBCommandFactory.h"
#include "CrystalVDB/VDBCommand/VDBInitCommand.h"

using namespace Crystal::VDB;

TEST(VDBCommandFactoryTest, TestCreate)
{
	VDBCommandFactory factory;
	EXPECT_FALSE( factory.createCommand(VDBInitCommand::getName()) == nullptr);
}