#include "gtest/gtest.h"

#include "../IO/PCDFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PCDFileWriterTest, TestWriteAscii)
{
	PCDFile pcd;
	pcd.header.width = 3;
	pcd.header.points = 3;
	pcd.data.positions.push_back(Vector3dd(1, 2, 3));
	pcd.data.positions.push_back(Vector3dd(2, 3, 4));
	pcd.data.positions.push_back(Vector3dd(3, 4, 5));

	PCDFileWriter writer;
	EXPECT_TRUE( writer.writeAscii("PCDFileWriterTest.pcd", pcd) );
}

TEST(PCDFileWriterTest, TestWriterBinary)
{
	PCDFile pcd;
	pcd.header.width = 3;
	pcd.header.points = 3;
	pcd.data.positions.push_back(Vector3dd(1, 2, 3));
	pcd.data.positions.push_back(Vector3dd(2, 3, 4));
	pcd.data.positions.push_back(Vector3dd(3, 4, 5));

	PCDFileWriter writer;
	EXPECT_TRUE(writer.writeBinary("PCDBinaryFileWriterTest.pcd", pcd));
}