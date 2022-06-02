#include "VDBComposite.h"

#include "VDBVolumeScene.h"
#include "VDBVolumeImpl.h"

#include "openvdb/openvdb.h"
#include "openvdb/tools/Composite.h"

using namespace Crystal::VDB;

void VDBComposite::csgUnion(const VDBVolumeScene* lhs, const VDBVolumeScene* rhs, VDBVolumeScene* dest)
{
	auto mesh1 = lhs->getImpl()->getPtr()->deepCopy();
	auto mesh2 = rhs->getImpl()->getPtr()->deepCopy();
	openvdb::tools::csgUnion(*mesh1, *mesh2);
	dest->getImpl()->setPtr(mesh1);
}

void VDBComposite::csgIntersection(const VDBVolumeScene* lhs, const VDBVolumeScene* rhs, VDBVolumeScene* dest)
{
	auto mesh1 = lhs->getImpl()->getPtr()->deepCopy();
	auto mesh2 = rhs->getImpl()->getPtr()->deepCopy();
	openvdb::tools::csgIntersection(*mesh1, *mesh2);
	dest->getImpl()->setPtr(mesh1);
}

void VDBComposite::csgDifference(const VDBVolumeScene* lhs, const VDBVolumeScene* rhs, VDBVolumeScene* dest)
{
	auto mesh1 = lhs->getImpl()->getPtr()->deepCopy();
	auto mesh2 = rhs->getImpl()->getPtr()->deepCopy();
	openvdb::tools::csgDifference(*mesh1, *mesh2);
	dest->getImpl()->setPtr(mesh1);
}