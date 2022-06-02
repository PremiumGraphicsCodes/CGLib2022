#include "gtest\gtest.h"
#include "../IO/OBJFileReader.h"

using namespace Crystal::IO;

// from http://www.martinreddy.net/gfx/3d/OBJ.spec
TEST(OBJFileReaderTest, TestExampleSquare)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "f 1 2 3 4" << std::endl;
	OBJFileReader reader;
	reader.read(stream);
	const auto& obj = reader.getOBJ();
	EXPECT_EQ(4, obj.positions.size());
}

TEST(OBJFileReaderTest, TestExampleCube)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "f 1 2 3 4" << std::endl
		<< "f 8 7 6 5" << std::endl
		<< "f 4 3 7 8" << std::endl
		<< "f 5 1 4 8" << std::endl
		<< "f 5 6 2 1" << std::endl
		<< "f 2 6 7 3" << std::endl;

	OBJFileReader reader;
	reader.read(stream);
	const auto& obj = reader.getOBJ();
	EXPECT_EQ(8, obj.positions.size());
	EXPECT_EQ(0, obj.normals.size());
	EXPECT_EQ(1, obj.groups.size());
	EXPECT_EQ(6, obj.groups[0].faces.size());
}

TEST(OBJFileReaderTest, TestNegativeReferenceNumber)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 2.000000 2.000000" << std::endl
		<< "f -4 -3 -2 -1" << std::endl;
	OBJFileReader reader;
	reader.read(stream);
	const auto& obj = reader.getOBJ();
	EXPECT_EQ(4, obj.positions.size());
	EXPECT_EQ(1, obj.groups.size());
	EXPECT_EQ(1, obj.groups[0].faces.size() );
}

TEST(OBJFileReaderTest, TestExampleGroups)
{
	std::stringstream stream;
	stream
		<< "g front cube" << std::endl
		<< "f 1 2 3 4" << std::endl
		<< "g back cube" << std::endl
		<< "f 8 7 6 5" << std::endl
		<< "g right cube" << std::endl
		<< "f 4 3 7 8" << std::endl
		<< "g top cube" << std::endl
		<< "f 5 1 4 8" << std::endl
		<< "g left cube" << std::endl
		<< "f 5 6 2 1" << std::endl
		<< "g bottom cube" << std::endl
		<< "f 2 6 7 3" << std::endl
		<< "# 6 elements" << std::endl;

	OBJFileReader reader;
	reader.read(stream);
	const auto& obj = reader.getOBJ();
	EXPECT_EQ(6, obj.groups.size());
}

TEST(OBJFileReaderTest, TestExampleSmoothingGroup)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "v 4.000000 0.000000 -1.255298" << std::endl
		<< "v 4.000000 2.000000 -1.255298" << std::endl
		<< "# 6 vertices" << std::endl
		<< "g all" << std::endl
		<< "s 1" << std::endl
		<< "f 1 2 3 4" << std::endl
		<< "f 4 3 5 6" << std::endl
		<< "# 2 elements" << std::endl;

	OBJFileReader reader;
	reader.read(stream);
	const auto& obj = reader.getOBJ();
	EXPECT_EQ(2, obj.groups[0].faces.size());
	EXPECT_EQ(6, obj.positions.size());
}

TEST(OBJFileReaderTest, TestExampleTextureMappedSquare)
{
	std::stringstream stream;
	stream
		<< "mtllib master.mtl" << std::endl
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "vt 0.000000 1.000000 0.000000" << std::endl
		<< "vt 0.000000 0.000000 0.000000" << std::endl
		<< "vt 1.000000 0.000000 0.000000" << std::endl
		<< "vt 1.000000 1.000000 0.000000" << std::endl
		<< "# 4 vertices" << std::endl
		<< "usemtl wood" << std::endl
		<< "f 1/1 2/2 3/3 4/4" << std::endl
		<< "# 1 element" << std::endl;

	OBJFileReader reader;
	reader.read(stream);
	const auto& obj = reader.getOBJ();
	EXPECT_EQ(1, obj.groups[0].faces.size());
	EXPECT_EQ(4, obj.positions.size());
	EXPECT_EQ(4, obj.texCoords.size());
}

TEST(OBJFileReaderTest, TestReadGroup)
{
	std::stringstream stream;
	stream
		<< "g" << std::endl
		<< "f 1//1 2//1 4//1 3//1" << std::endl
		<< "f 6//2 5//2 7//2 8//2" << std::endl
		<< "f 1//3 3//3 7//3 5//3" << std::endl
		<< "f 2//4 6//4 8//4 4//4" << std::endl
		<< "f 3//5 4//5 8//5 7//5" << std::endl
		<< "f 1//6 5//6 6//6 2//6" << std::endl;

	OBJFileReader reader;
	EXPECT_TRUE(reader.read(stream));
	const auto obj = reader.getOBJ();
	EXPECT_EQ(1, obj.groups.size());
	EXPECT_EQ(6, obj.groups.front().faces.size());
}