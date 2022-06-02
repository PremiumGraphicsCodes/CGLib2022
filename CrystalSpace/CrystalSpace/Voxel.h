#pragma once

#include "../../Crystal/Shape/Volume.h"
#include "SparseVolume.h"

namespace Crystal {
	namespace Space {

using Voxel = Shape::Volume<bool>;
using SparseVoxel = SparseVolume<bool>;

	}
}