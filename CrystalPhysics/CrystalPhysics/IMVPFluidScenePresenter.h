#pragma once

#include "CrystalScene/Scene/IPresenter.h"

namespace Crystal {
	namespace Physics {
		class IMVPFluidScene;

class IMVPFluidScenePresenter : public Scene::IPresenter
{
public:
	explicit IMVPFluidScenePresenter(IMVPFluidScene* model)
	{}

	virtual ~IMVPFluidScenePresenter() {};
};

	}
}