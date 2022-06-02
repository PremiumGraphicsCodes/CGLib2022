#include <gtest/gtest.h>

#include "../CrystalSpace/LinearOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

namespace {
	constexpr auto tolerance = 1.0e-12;
}

TEST(LinearOctreeIndexTest, TestGetIndex1d)
{
	{
		const LinearOctreeIndex index(1, 7);
		EXPECT_EQ(8, index.getIndex1d());
	}

	{
		const LinearOctreeIndex index(2, 0);
		EXPECT_EQ(9, index.getIndex1d());
	}

	{
		const LinearOctreeIndex index(2, 5);
		EXPECT_EQ(14, index.getIndex1d());
	}
}

TEST(LinearOctreeIndexTest, TestGetLevelAndNumber)
{
	{
		const LinearOctreeIndex index(1, 1);
		const auto ln = index.getLevelAndNumber();
		EXPECT_EQ(1, ln.first);
		EXPECT_EQ(1, ln.second);
	}
}

TEST(LinearOctreeIndexTest, TestGetParentIndex)
{
	{
		const LinearOctreeIndex index(1, 1);
		const auto actual = index.getParentIndex();

		const LinearOctreeIndex expected(0, 0);
		EXPECT_EQ(expected, actual);
	}

	{
		const LinearOctreeIndex index(2, 20);
		const auto actual = index.getParentIndex();

		const LinearOctreeIndex expected(1, 2);
		EXPECT_EQ(expected, actual);
	}
}

TEST(LinearOctreeTest, TestInit)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	{
		LinearOctree treeOperator;
		treeOperator.init(space, 0);
		EXPECT_EQ(treeOperator.getTable().size(), 1);
	}

	{
		LinearOctree treeOperator;
		treeOperator.init(space, 1);
		EXPECT_EQ(treeOperator.getTable().size(), 9);
	}

	{
		LinearOctree treeOperator;
		treeOperator.init(space, 2);
		EXPECT_EQ(treeOperator.getTable().size(), 73);
	}

	//treeOperator.
}

TEST(LinearOctreeTest, TestCalculateAABB)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));

	LinearOctree treeOperator;
	treeOperator.init(space, 2);

	const auto expected0 = space;
	const auto bb0 = treeOperator.calculateAABB(LinearOctreeIndex(0));
	EXPECT_TRUE(bb0.isSame(expected0, tolerance));

	const Box3dd expected1(Vector3dd(0, 0, 0), Vector3dd(5, 5, 5));
	const auto bb1 = treeOperator.calculateAABB(LinearOctreeIndex(1));
	EXPECT_TRUE(bb1.isSame(expected1, tolerance));

	const Box3dd expected2(Vector3dd(5, 0, 0), Vector3dd(10, 5, 5));
	const auto bb2 = treeOperator.calculateAABB(LinearOctreeIndex(2));
	EXPECT_TRUE(bb2.isSame(expected2, tolerance));

	const Box3dd expected3(Vector3dd(0, 5, 0), Vector3dd(5, 10, 5));
	const auto bb3 = treeOperator.calculateAABB(LinearOctreeIndex(3));
	EXPECT_TRUE(bb3.isSame(expected3, tolerance));
}

TEST(LinearOctreeTest, TestCalculateAABBFromIndices)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	LinearOctree treeOperator;
	treeOperator.init(space, 2);

	const Box3dd expected1(Vector3dd(0, 0, 0), Vector3dd(2.5, 2.5, 2.5));
	const auto bb1 = treeOperator.calculateAABB({ 0,0,0 });
	EXPECT_TRUE(expected1.isSame(bb1, tolerance));

	const Box3dd expected2(Vector3dd(2.5, 0, 0), Vector3dd(5.0, 2.5, 2.5));
	const auto bb2 = treeOperator.calculateAABB({ 1,0,0 });
	EXPECT_TRUE(expected2.isSame(bb2, tolerance));
}

TEST(LinearOctreeTest, TestMinBoxSize)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	LinearOctree treeOperator;
	treeOperator.init(space, 2);
	const auto actual = treeOperator.getMinBoxSize();
	const Vector3dd expected(2.5, 2.5, 2.5);
	EXPECT_TRUE(areSame(expected, actual, tolerance));
}

TEST(LinearOctreeTest, TestGetParentLevel)
{
	{
		const Box3dd rootSpace(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
		LinearOctree treeOperator;
		treeOperator.init(rootSpace, 1);
		
		const Box3dd space1(Vector3dd(0, 0, 0), Vector3dd(9, 3, 3));
		EXPECT_EQ(LinearOctreeIndex(0, 0), treeOperator.getIndex(space1));

		const Box3dd space2(Vector3dd(0, 0, 0), Vector3dd(1, 1, 1));
		EXPECT_EQ(LinearOctreeIndex(1, 0), treeOperator.getIndex(space2));

		const Box3dd space3(Vector3dd(7, 7, 7), Vector3dd(8, 8, 8));
		EXPECT_EQ(LinearOctreeIndex(1, 7), treeOperator.getIndex(space3));
		//	const auto bb = treeOperator.calculateAABB(LinearOctreeIndex(1, 7));

		const Box3dd space4(Vector3dd(7, 0, 0), Vector3dd(8, 0, 0));
		EXPECT_EQ(LinearOctreeIndex(1, 1), treeOperator.getIndex(space4));
	}

	{
		const Box3dd rootSpace(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
		LinearOctree treeOperator;
		treeOperator.init(rootSpace, 4);

		const Box3dd space(Vector3dd(8, 8, 8), Vector3dd(8, 8, 8));
		EXPECT_EQ(LinearOctreeIndex(4, 4032), treeOperator.getIndex(space));
		//const auto bb = treeOperator.calculateAABB(LinearOctreeIndex(4, 4032));
	}

}

TEST(LinearOctreeTest, TestAdd)
{
	const Box3dd space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	LinearOctree treeOperator;
	treeOperator.init(space, 2);
	LinearOctreeItem item(Box3dd(Vector3dd(3, 3, 3), Vector3dd(6, 6, 6)));
	treeOperator.add(&item);
	const auto items = treeOperator.findItems(Box3dd(Vector3dd(3, 3, 3), Vector3dd(6, 6, 6)));
	EXPECT_EQ(items.size(), 1);
}
