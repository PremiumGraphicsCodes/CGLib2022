#include "gtest/gtest.h"

#include "../IO/STLFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(STLASCIILFileWriterTest, TestWrite)
{
	const Triangle3d t1
	(
		Vector3dd(0, 1, 2),
		Vector3dd(3, 4, 5),
		Vector3dd(6, 7, 8)
	);
	const Triangle3d t2
	(
		Vector3dd(10, 11, 12),
		Vector3dd(13, 14, 15),
		Vector3dd(16, 17, 18)
	);
	const Triangle3d t3
	(
		Vector3dd(0, 0, 0),
		Vector3dd(1, 0, 0),
		Vector3dd(0, 1, 0)
	);


	STLFile stl;
	stl.header = "";
	stl.faceCount = 3;
	stl.faces.push_back(STLFace(t1, Vector3dd(0,0,1)));
	stl.faces.push_back(STLFace(t2, Vector3dd(0,0,1)));
	stl.faces.push_back(STLFace(t3, Vector3dd(0,0,1)));

	STLFileWriter writer;
	writer.writeAscii("STLASCIIFileWriterTest.stl", stl);
}
