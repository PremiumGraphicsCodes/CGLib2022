#include "VDBTransform.h"

#include <openvdb/openvdb.h>
#include <openvdb/tools/GridTransformer.h>
#include "VDBVolumeImpl.h"

using namespace Crystal::VDB;

void VDBTransform::transformGeometry()
{
	auto sourceGrid = source->getImpl()->getPtr();
	auto targetGrid = target->getImpl()->getPtr();

	const openvdb::math::Transform& sourceXform = sourceGrid->transform();
	const auto& targetXform = targetGrid->transform();
	
	// Compute a source grid to target grid transform.
	// // (For this example, we assume that both grids' transforms are linear,
	// so that they can be represented as 4 x 4 matrices.)
	openvdb::Mat4R xform = sourceXform.baseMap()->getAffineMap()->getMat4() * targetXform.baseMap()->getAffineMap()->getMat4().inverse();

	// Create the transformer.
	openvdb::tools::GridTransformer transformer(xform);
	// Resample using nearest-neighbor interpolation.
	transformer.transformGrid<openvdb::tools::PointSampler, openvdb::FloatGrid>(*sourceGrid, *targetGrid);

/*
// Resample using trilinear interpolation.
transformer.transformGrid<openvdb::tools::BoxSampler, openvdb::FloatGrid>(
	*sourceGrid, *targetGrid);
// Resample using triquadratic interpolation.
transformer.transformGrid<openvdb::tools::QuadraticSampler, openvdb::FloatGrid>(
	*sourceGrid, *targetGrid);
	*/
	// Prune the target tree for optimal sparsity.
	//targetGrid->tree().prune();

}