#include "gtest/gtest.h"

#include "../IO/OBJFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(OBJFileWriterTest, TestWrite)
{
	OBJFile obj;
	obj.positions.push_back(Vector3dd(0, 0, 0));
	obj.positions.push_back(Vector3dd(1, 0, 0));
	obj.positions.push_back(Vector3dd(1, 1, 0));
	obj.positions.push_back(Vector3dd(0, 1, 0));
	obj.normals.push_back(Vector3dd(0, 0, 1));
	obj.texCoords.push_back(Vector2dd(0.0, 0.0));
	obj.texCoords.push_back(Vector2dd(1.0, 0.0));
	obj.texCoords.push_back(Vector2dd(1.0, 1.0));
	obj.texCoords.push_back(Vector2dd(0.0, 1.0));

	OBJFace face1;
	face1.positionIndices = { 1,2,4 };
	face1.normalIndices = { 1, 1, 1 };
	face1.texCoordIndices = { 1,2,4 };

	OBJFace face2;
	face1.positionIndices = { 3,4,2 };
	face1.normalIndices = { 1, 1, 1 };
	face1.texCoordIndices = { 3,4,2 };

	OBJGroup group;
	group.faces.push_back(face1);
	group.faces.push_back(face2);
	obj.groups.push_back(group);

	OBJFileWriter writer;
	EXPECT_TRUE( writer.write("OBJFileWriterTest.obj", obj) );
}