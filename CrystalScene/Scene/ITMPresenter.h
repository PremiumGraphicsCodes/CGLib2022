#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class TriangleMeshScene;

class ITMPresenter : public IPresenter
{
public:
	explicit ITMPresenter(TriangleMeshScene* model) :
		model(model)
	{}

	virtual ~ITMPresenter() {}

	//PolygonMeshScene* getModel()

protected:
	TriangleMeshScene* model;
};

	}
}