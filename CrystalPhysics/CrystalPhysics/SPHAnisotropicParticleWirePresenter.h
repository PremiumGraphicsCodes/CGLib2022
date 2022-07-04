#pragma once

#include "ISPHAnisotropicParticlePresenter.h"

#include "CrystalScene/Scene/LineShaderScene.h"

namespace Crystal {
	namespace Physics {

class SPHAnisotropicParticleWirePresenter : public ISPHAnisotropicParticlePresenter
{
public:
	explicit SPHAnisotropicParticleWirePresenter(SPHAnisotropicParticleScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override;

	void updateView() override;

private:
	SPHAnisotropicParticleScene* model;
	Scene::LineShaderScene* view;
};

	}
}