#include "VDBResampler.h"
#include "VDBVolumeImpl.h"

#include "openvdb/openvdb.h"
#include "openvdb/tools/Interpolation.h"

using namespace Crystal::VDB;

void VDBResampler::box()
{
	openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::BoxSampler> sampler(*src->getImpl()->getPtr());
}

void VDBResampler::point()
{
	openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::PointSampler> sampler(*src->getImpl()->getPtr());
}

void VDBResampler::quadratic()
{
	openvdb::tools::GridSampler<openvdb::FloatGrid, openvdb::tools::QuadraticSampler> sampler(*src->getImpl()->getPtr());
}
