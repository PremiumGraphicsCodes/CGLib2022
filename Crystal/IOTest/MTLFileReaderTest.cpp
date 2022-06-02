#include "gtest/gtest.h"

#include "../Shape/PolygonMeshBuilder.h"
#include "../IO/MTLFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

TEST(MTLFileReaderTest, TestRead)
{
	std::stringstream stream;
	stream
		<< "newmtl FrontColor" << std::endl
		<< "Ka 0.0 0.0 0.0" << std::endl
		<< "Kd 1.0 1.0 1.0" << std::endl
		<< "Ks 0.1 0.1 0.1" << std::endl
		<< "illum 0" << std::endl;

	MTLFileReader reader;
	EXPECT_TRUE(reader.read(stream));
	const auto& m = reader.getMTL();
	const auto& mtl = m.materials[0];

	EXPECT_EQ(mtl.name, "FrontColor");
	EXPECT_EQ(mtl.ambient, ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f));
	EXPECT_EQ(mtl.diffuse, ColorRGBAf(1.0f, 1.0f, 1.0f, 0.0f));
	EXPECT_EQ(mtl.specular, ColorRGBAf(0.1f, 0.1f, 0.1f, 0.0f));
}

TEST(MTLFileReaderTest, TestReadTexture)
{
	std::stringstream stream;
	stream
		<< "newmtl name" << std::endl
		<< "map_Ka ambient.png" << std::endl
		<< "map_Kd diffuse.png" << std::endl
		<< "map_Ks shininess.png" << std::endl
		<< "bump bump.png" << std::endl;

	MTLFileReader reader;
	EXPECT_TRUE(reader.read(stream));
	const auto& m = reader.getMTL();
	const auto& mtl = m.materials[0];

	EXPECT_EQ(mtl.name, "name");
	EXPECT_EQ(mtl.ambientTexture, "ambient.png");
	EXPECT_EQ(mtl.diffuseTexture, "diffuse.png");
	EXPECT_EQ(mtl.shininessTexture, "shininess.png");
	EXPECT_EQ(mtl.bumpTexture, "bump.png");
}


// from http://paulbourke.net/dataformats/mtl/
TEST(MTLFileReaderTest, TestExample1)
{
	std::stringstream stream;
	stream
		<< "newmtl neon_green" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "illum 0" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));

	const auto& m = file.getMTL();
	const auto& mtl = m.materials;

	EXPECT_EQ(1, mtl.size());
	EXPECT_EQ("neon_green", mtl.front().name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.front().diffuse);
	EXPECT_EQ(MTL::Illumination::COLOR_ON_AND_AMBIENT_OFF, mtl.front().illumination);
}

TEST(MTLFileReaderTest, TestExample2)
{
	std::stringstream stream;
	stream
		<< "newmtl flat_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "illum 1" << std::endl;
	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));

	const auto& mtl = file.getMTL();
	EXPECT_EQ(1, mtl.materials.size());

	const auto& m = mtl.materials[0];
	EXPECT_EQ("flat_green", m.name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), m.ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), m.diffuse);
	EXPECT_EQ(MTL::Illumination::COLOR_ON_AND_AMBIENT_ON, m.illumination);

}

TEST(MTLFileReaderTest, TestExample3)
{
	std::stringstream stream;
	stream
		<< "newmtl diss_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "d 0.8000" << std::endl
		<< "illum 1" << std::endl;

	MTLFileReader reader;
	EXPECT_TRUE(reader.read(stream));

	const auto& mtl = reader.getMTL();
	EXPECT_EQ(1, mtl.materials.size());

	const auto& m = mtl.materials[0];
	EXPECT_EQ("diss_green", m.name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), m.ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), m.diffuse);
	EXPECT_FLOAT_EQ(0.8f, m.transparent);
	EXPECT_EQ(MTL::Illumination::COLOR_ON_AND_AMBIENT_ON, m.illumination);
}

TEST(MTLFileReaderTest, TestExample4)
{
	std::stringstream stream;
	stream
		<< "newmtl shiny_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "Ks 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200.0000" << std::endl
		<< "illum 1" << std::endl;

	MTLFileReader reader;
	EXPECT_TRUE(reader.read(stream));
	const auto& m = reader.getMTL();
	EXPECT_EQ(1, m.materials.size());

	const MTL& mtl = m.materials.front();
	EXPECT_EQ("shiny_green", mtl.name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.diffuse);
	EXPECT_EQ(ColorRGBAf(1.0, 1.0, 1.0, 0.0), mtl.specular);
	EXPECT_FLOAT_EQ(200.0f, mtl.specularExponent);
	EXPECT_EQ(MTL::Illumination::COLOR_ON_AND_AMBIENT_ON, mtl.illumination);
}

TEST(MTLFileReaderTest, TestExample5)
{
	std::stringstream stream;
	stream
		<< "newmtl green_mirror" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "Ks 0.0000 1.0000 0.0000" << std::endl
		<< "Ns 200.0000" << std::endl
		<< "illum 3" << std::endl;

	MTLFileReader reader;
	EXPECT_TRUE(reader.read(stream));

	const auto& m = reader.getMTL();
	EXPECT_EQ(1, m.materials.size());
	const MTL& mtl = m.materials[0];
	EXPECT_EQ("green_mirror", mtl.name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.diffuse);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.specular);
	EXPECT_FLOAT_EQ(200.0f, mtl.specularExponent);
	EXPECT_EQ(MTL::Illumination::REFRECTION_ON_AND_RAY_TRACE_ON, mtl.illumination);
}

TEST(MTLFileReaderTest, TestExample6)
{
	std::stringstream stream;
	stream
		<< "newmtl fake_windsh" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.9000 0.9000 0.9000" << std::endl
		<< "d 0.1000" << std::endl
		<< "Ns 200" << std::endl
		<< "illum 4" << std::endl;

	MTLFileReader reader;
	EXPECT_TRUE(reader.read(stream));

	const auto& m = reader.getMTL();
	EXPECT_EQ(1, m.materials.size());
	const MTL& mtl = m.materials.front();
	EXPECT_EQ("fake_windsh", mtl.name);
	EXPECT_EQ(ColorRGBAf(0.0, 0.0, 0.0, 0.0), mtl.ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 0.0, 0.0, 0.0), mtl.diffuse);
	EXPECT_EQ(ColorRGBAf(0.9f, 0.9f, 0.9f, 0.0), mtl.specular);
	EXPECT_FLOAT_EQ(200.0f, mtl.specularExponent);
//	EXPECT_EQ(4, mtl.illumination);
}

TEST(MTLFileReaderTest, TestExample7)
{
	std::stringstream stream;
	stream
		<< "newmtl fresnel_blue" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.6180 0.8760 0.1430" << std::endl
		<< "Ns 200" << std::endl
		<< "illum 5" << std::endl;

	MTLFileReader reader;
	EXPECT_TRUE(reader.read(stream));
	const auto& m = reader.getMTL();
	EXPECT_EQ(1, m.materials.size());
	const MTL& mtl = m.materials.front();
	EXPECT_EQ("fresnel_blue", mtl.name);
	EXPECT_EQ(ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f), mtl.ambient);
	EXPECT_EQ(ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f), mtl.diffuse);
	EXPECT_EQ(ColorRGBAf(0.6180f, 0.8760f, 0.1430f, 0.0f), mtl.specular);
	EXPECT_FLOAT_EQ(200.0f, mtl.specularExponent);
	//EXPECT_EQ(5, mtl.illumination);
}

TEST(MTLFileReaderTest, TestExample8)
{
	std::stringstream stream;
	stream
		<< "newmtl real_windsh" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.0000 0.0000 0.0000" << std::endl
		<< "Tf 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200" << std::endl
		<< "Ni 1.2000" << std::endl
		<< "illum 6" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));
	const auto& m = file.getMTL();
	EXPECT_EQ(1, m.materials.size());
	const MTL& mtl = m.materials.front();
	EXPECT_EQ("real_windsh", mtl.name);
	EXPECT_FLOAT_EQ(1.2f, mtl.opticalDensity);
}

TEST(MTLFileReaderTest, TestReadMaterials)
{
	std::stringstream stream;
	stream
		<< "newmtl mat1" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.0000 0.0000 0.0000" << std::endl
		<< "Tf 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200" << std::endl
		<< "Ni 1.2000" << std::endl
		<< "illum 6" << std::endl
		<< "newmtl mat2" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.0000 0.0000 0.0000" << std::endl
		<< "Tf 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200" << std::endl
		<< "Ni 1.2000" << std::endl
		<< "illum 6" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));
	const auto& mtl = file.getMTL();
	EXPECT_EQ(2, mtl.materials.size());
	EXPECT_EQ("mat1", mtl.materials[0].name);
	EXPECT_FLOAT_EQ(1.2f, mtl.materials[0].opticalDensity);
	EXPECT_EQ("mat2", mtl.materials[1].name);
}