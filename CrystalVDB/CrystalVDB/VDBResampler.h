#pragma once

#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {

class VDBResampler
{
public:
	void setSource(VDBVolumeScene* src) { this->src = src; }

	void box();

	void point();

	void quadratic();

private:
	VDBVolumeScene* src = nullptr;
};

	}
}