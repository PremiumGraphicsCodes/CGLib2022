#include "pch.h"

#include "../VDBCommand/VDBCommandFactory.h"
#include "../VDBCommand/VDBInitCommand.h"
#include "../VDBCommand/VDBSceneCreateCommand.h"

#include "../VDBCommand/VDBSceneFileReadCommand.h"
#include "../VDBCommand/VDBSceneFileWriteCommand.h"
#include "../VDBCommand/VDBSceneFilterCommand.h"
#include "../VDBCommand/VDBSceneCompositeCommand.h"
#include "../VDBCommand/VDBSceneResamplingCommand.h"
#include "../VDBCommand/VDBScenePSToVolumeCommand.h"
#include "../VDBCommand/VDBSceneMeshToVolumeCommand.h"
#include "../VDBCommand/VDBSceneVolumeToMeshCommand.h"
#include "../VDBCommand/VDBSceneVolumeToPointsCommand.h"

#include "CrystalScene/Command/JSONFileWriter.h"
#include "CrystalScene/Command/JSONFileReader.h"

using namespace Crystal::VDB;
using namespace Crystal::Command;

TEST(VDBRunnerTest, TestInitCommand)
{
	const std::string filepath("./TestFiles/init.json");

	VDBInitCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE( writer.write(filepath) );

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE( reader.read(filepath, factory) );
}

TEST(VDBRunnerTest, TestPointsSceneCreateCommand)
{
	const std::string filepath("./TestFiles/vdb_scene_create_points.json");

	VDBSceneCreateCommand command;
	VDBSceneCreateCommand::Args args;
	args.sceneType.setValue(std::string("VDBPoints"));
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneFileWriteCommand)
{
	const std::string filepath = "./TestFiles/scene_write.json";
	VDBSceneFileWriteCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneFileReadCommand)
{
	const std::string filepath = "./TestFiles/scene_read.json";
	VDBSceneFileReadCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneFilterCommand)
{
	const std::string filepath = "./TestFiles/scene_filter.json";
	VDBSceneFilterCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneCompositeCommand)
{
	const std::string filepath = "./TestFiles/scene_composite.json";
	VDBSceneCompositeCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneResamplingCommand)
{
	const std::string filepath = "./TestFiles/scene_resampling.json";
	VDBSceneResamplingCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestScenePSToVolumeCommand)
{
	const std::string filepath = "./TestFiles/scene_ps_to_volume.json";
	VDBScenePSToVolumeCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneMeshToVolumeCommand)
{
	const std::string filepath = "./TestFiles/scene_mesh_to_volume.json";
	VDBSceneMeshToVolumeCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneVolumeToMeshCommand)
{
	const std::string filepath("./TestFiles/scene_volume_to_mesh.json");

	VDBSceneVolumeToMeshCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}

TEST(VDBRunnerTest, TestSceneVolumeToPointsCommand)
{
	const std::string filepath("./TestFiles/scene_volume_to_points.json");

	VDBSceneVolumeToPointsCommand command;
	JSONFileWriter writer;
	writer.add(&command);
	EXPECT_TRUE(writer.write(filepath));

	VDBCommandFactory factory;
	JSONFileReader reader;
	EXPECT_TRUE(reader.read(filepath, factory));
}
