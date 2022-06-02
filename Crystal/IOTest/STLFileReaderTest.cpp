#include "gtest/gtest.h"

#include "../Math/Vector3d.h"
#include "../IO/STLFileReader.h"
#include "../IO/STLFileReader.h"

namespace {
	std::stringstream getSampleAscii() {
		std::stringstream stream;
		stream
			<< "solid cube-ascii" << std::endl
			<< "facet normal  0.0  0.0 1.0" << std::endl
			<< "	outer loop" << std::endl
			<< "		vertex  0.0  0.0  1.0" << std::endl
			<< "		vertex  1.0  0.0  1.0" << std::endl
			<< "		vertex  0.0  1.0  1.0" << std::endl
			<< "endloop" << std::endl
			<< "endfacet" << std::endl
			<< "facet normal 0.0 0.0 1.0" << std::endl
			<< "	outer loop" << std::endl
			<< "		vertex  1.0  1.0  1.0" << std::endl
			<< "		vertex  0.0  1.0  1.0" << std::endl
			<< "		vertex  1.0  0.0  1.0" << std::endl
			<< "	endloop" << std::endl
			<< "endfacet" << std::endl
			<< "endsolid" << std::endl;
		return stream;
	}

}

using namespace Crystal::IO;

TEST(STLFileReaderTest, TestIsBinary)
{
	auto stream = getSampleAscii();

	STLFileReader reader;
	EXPECT_FALSE(reader.isBinary(stream));
	/*
	const auto& faces = reader.getSTL().faces;

	EXPECT_EQ(2, faces.size());

	const auto& face1 = faces[0];
	EXPECT_EQ(Vector3dd(0, 0, 1), face1.normal);
	EXPECT_EQ(Vector3dd(0, 0, 1), face1.triangle.getVertices()[0]);
	EXPECT_EQ(Vector3dd(1, 0, 1), face1.triangle.getVertices()[1]);
	EXPECT_EQ(Vector3dd(0, 1, 1), face1.triangle.getVertices()[2]);

	const auto& face2 = faces[1];
	EXPECT_EQ(Vector3dd(0, 0, 1), face2.normal);
	EXPECT_EQ(Vector3dd(1, 1, 1), face2.triangle.getVertices()[0]);
	EXPECT_EQ(Vector3dd(0, 1, 1), face2.triangle.getVertices()[1]);
	EXPECT_EQ(Vector3dd(1, 0, 1), face2.triangle.getVertices()[2]);
	*/
}