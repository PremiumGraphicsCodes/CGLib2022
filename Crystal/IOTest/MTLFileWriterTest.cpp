#include "gtest/gtest.h"

#include "../IO/MTLFileWriter.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;

TEST(MTLFileWriterTest, TestWrite)
{
	MTL m;
	m.ambient = ColorRGBAf(1, 0, 0, 0);
	m.diffuse = ColorRGBAf(0, 1, 0, 0);
	m.specular = ColorRGBAf(0, 0, 1, 0);
	m.ambientTexture = "AmbientTex";
	m.diffuseTexture = "DiffuseTex";
	m.shininessTexture = "ShininessTex";
	m.specularExponent = 1.1f;
	m.name = "Sample";

	MTLFile mtl;
	mtl.materials.push_back(m);

	MTLFileWriter writer;
	EXPECT_TRUE( writer.write("MTLFileWriteTest.mtl", mtl) );
}