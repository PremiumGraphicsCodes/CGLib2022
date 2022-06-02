#include "VDBAdapter.h"

#include <openvdb/openvdb.h>

using namespace Crystal::VDB;

void VDBAdapter::init()
{
	openvdb::initialize();
}
