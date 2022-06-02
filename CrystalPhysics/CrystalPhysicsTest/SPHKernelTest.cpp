#include "pch.h"
#include "../CrystalPhysics/SPHKernel.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(SPHKernelTest, TestGetPoly6Kernel)
{
	SPHKernel kernel(1.0);
	const auto actual = kernel.getPoly6Kernel(1.0);
	EXPECT_EQ(0.0, actual);
}