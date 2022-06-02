#include "gtest/gtest.h"

#include "../IO/PLYFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PLYFileReaderTest, TestReadASCII)
{
	PLYFileReader reader;
	const auto isOk = reader.read("PLYWriteTestASCII.ply");
	EXPECT_TRUE(isOk);
	EXPECT_EQ(3, reader.getPLY().vertices.size());
}

TEST(PLYFileReaderTest, TestReadBinary)
{
	PLYFileReader reader;
	const auto isOk = reader.read("PLYWriteTestBinary.ply");
	EXPECT_TRUE(isOk);
	EXPECT_EQ(3, reader.getPLY().vertices.size());
}