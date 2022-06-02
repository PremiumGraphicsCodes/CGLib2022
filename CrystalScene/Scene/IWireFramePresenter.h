#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class WireFrameScene;

class IWireFramePresenter : public IPresenter
{
public:
	explicit IWireFramePresenter(WireFrameScene* model) :
		model(model)
	{}

	virtual ~IWireFramePresenter() {}

protected:
	WireFrameScene* model;
};

	}
}