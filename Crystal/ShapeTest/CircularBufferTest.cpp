#include "pch.h"

#include "../Shape/CircularBuffer.h"

using namespace Crystal::Shape;

TEST(CircularBufferTest, TestGetSet)
{
	CircularBuffer<int> buffer(10);
	buffer.set(10, 314);
	EXPECT_EQ(314, buffer.get(0));
	EXPECT_EQ(314, buffer[0]);
	EXPECT_EQ(314, buffer.get(10));
	EXPECT_EQ(314, buffer[10]);

	buffer.set(1, 315);
	EXPECT_EQ(315, buffer.get(11));
	EXPECT_EQ(315, buffer[11]);
}
