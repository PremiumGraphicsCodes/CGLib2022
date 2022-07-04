#pragma once

#include "CrystalScene/Scene/IPresenter.h"

namespace Crystal {
	namespace Physics {

class SPHAnisotropicParticleScene;

class ISPHAnisotropicParticlePresenter : public Scene::IPresenter
{
public:
	explicit ISPHAnisotropicParticlePresenter(SPHAnisotropicParticleScene* model) {};

	virtual ~ISPHAnisotropicParticlePresenter() {};
};

	}
}