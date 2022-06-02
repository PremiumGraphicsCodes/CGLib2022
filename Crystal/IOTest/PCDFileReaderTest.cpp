#include "gtest\gtest.h"
#include "../IO/PCDFileReader.h"

using namespace Crystal::IO;

// from http://pointclouds.org/documentation/tutorials/pcd_file_format.php
TEST(PCDFileReaderTest, TestReadASCII)
{
	std::stringstream stream;
	stream
		<< "# .PCD v.7 - Point Cloud Data file format" << std::endl
		<< "VERSION .7" << std::endl
		<< "FIELDS x y z rgb" << std::endl
		<< "SIZE 4 4 4 4" << std::endl
		<< "TYPE F F F F" << std::endl
		<< "COUNT 1 1 1 1" << std::endl
		<< "WIDTH 213" << std::endl
		<< "HEIGHT 1" << std::endl
		<< "VIEWPOINT 0 0 0 1 0 0 0" << std::endl
		<< "POINTS 213" << std::endl
		<< "DATA ascii" << std::endl
		<< "0.93773 0.33763 0 4.2108e+06" << std::endl
		<< "0.90805 0.35641 0 4.2108e+06" << std::endl
		<< "0.81915 0.32 0 4.2108e+06" << std::endl
		<< "0.97192 0.278 0 4.2108e+06" << std::endl
		<< "0.944 0.29474 0 4.2108e+06" << std::endl;
	PCDFileReader reader;
	EXPECT_TRUE( reader.readAscii(stream) );

	const auto& pcd = reader.getPCD();
	EXPECT_EQ(5, pcd.data.positions.size()) << std::endl;
}

// from http://pointclouds.org/documentation/tutorials/pcd_file_format.php
TEST(PCDFileReaderTest, TestReadBinary)
{
	PCDFileReader reader;
	EXPECT_TRUE(reader.readBinary("./PCDBinaryFileWriterTest.pcd"));

	const auto& pcd = reader.getPCD();
	EXPECT_EQ(3, pcd.data.positions.size()) << std::endl;
}
