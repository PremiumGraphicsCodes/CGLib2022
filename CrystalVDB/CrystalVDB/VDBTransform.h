#pragma once

#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {

class VDBTransform
{
public:
	enum class TransformType{
		Point,
		Box,
		Quad,
	};

	void transformGeometry();

private:
	VDBVolumeScene* source = nullptr;
	VDBVolumeScene* target = nullptr;

};

	}
}