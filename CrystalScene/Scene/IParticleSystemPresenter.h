#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;

class IParticleSystemPresenter : public IPresenter
{
public:
	explicit IParticleSystemPresenter(ParticleSystemScene* model) :
		model(model)
	{}

	virtual ~IParticleSystemPresenter() {}

protected:
	ParticleSystemScene* model;
};

	}
}