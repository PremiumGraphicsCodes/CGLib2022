#pragma once

#include "VDBVolumeScene.h"

namespace Crystal {
	namespace VDB {

class VDBFilter
{
public:
	void setSource(VDBVolumeScene* src) { this->src = src; }

	void median(const int width, const int iteration);

	void mean(const int width, const int iteration);

	void gaussian(const int width, const int iteration);

	//std::unique_ptr<VDBVolumeScene> getFiltered() { return std::move(filtered); }

private:
	VDBVolumeScene* src = nullptr;
	//VDBVolumeScene* dest = nullptr;
	//std::unique_ptr<VDBVolumeScene> filtered;
};

	}
}