#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;

class IPMPresenter : public IPresenter
{
public:
	explicit IPMPresenter(PolygonMeshScene* model) :
		model(model)
	{}

	virtual ~IPMPresenter() {}

	//PolygonMeshScene* getModel()

protected:
	PolygonMeshScene* model;

};

	}
}