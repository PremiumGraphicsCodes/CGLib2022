#include "VDBFilter.h"

#include "VDBVolumeImpl.h"

#include "openvdb/openvdb.h"
#include "openvdb/tools/Filter.h"

using namespace Crystal::VDB;

void VDBFilter::median(const int width, const int iteration)
{
	auto grid = this->src->getImpl()->getPtr();
	openvdb::tools::Filter<openvdb::FloatGrid> filter(*grid);
	filter.median(width, iteration);
}

void VDBFilter::mean(const int width, const int iteration)
{
	auto grid = this->src->getImpl()->getPtr();
	openvdb::tools::Filter<openvdb::FloatGrid> filter(*grid);
	filter.mean(width, iteration);
}

void VDBFilter::gaussian(const int width, const int iteration)
{
	auto grid = this->src->getImpl()->getPtr();
	openvdb::tools::Filter<openvdb::FloatGrid> filter(*grid);
	filter.gaussian(width, iteration);
}
