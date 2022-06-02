#include "gtest/gtest.h"

#include "../Math/Vector3d.h"
#include "../IO/TXTFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

namespace {
	std::stringstream getSampleTXT() {
		std::stringstream stream;
		stream
			<< "0.0 0.0 1.0" << std::endl
			<< "1.0 0.0 1.0" << std::endl
			<< "0.0 1.0 1.0" << std::endl;
		return stream;
	}
}

TEST(TXTFileReaderTest, TestRead)
{
	auto stream = getSampleTXT();

	TXTFileReader reader;
	EXPECT_TRUE(reader.read(stream));

	EXPECT_EQ(3, reader.getPositions().size());
}