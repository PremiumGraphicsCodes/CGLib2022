#pragma once

#include "ISPHAnisotropicParticlePresenter.h"

#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"
#include "Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Physics {

class SPHAnisotropicParticleScenePresenter : public ISPHAnisotropicParticlePresenter
{
public:
	explicit SPHAnisotropicParticleScenePresenter(SPHAnisotropicParticleScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override {};

	void updateView() override;

	void setColorMap(const Graphics::ColorMap& cm) { this->colorMap = cm; }

private:
	SPHAnisotropicParticleScene* model;
	Scene::PointShaderScene* view;
	Graphics::ColorMap colorMap;
};



	}
}