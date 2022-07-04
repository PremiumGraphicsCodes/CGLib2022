#pragma once

#include "CrystalScene/Scene/IPresenter.h"

#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"
#include "Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Physics {
		class SPHAnisotropicParticleScene;

class SPHAnisotropicParticleScenePresenter : public Scene::IPresenter
{
public:
	explicit SPHAnisotropicParticleScenePresenter(SPHAnisotropicParticleScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override {};

	void updateView() override;

	enum class Mode
	{
		Uniform,
		Density,
	};

	void setColorMap(const Graphics::ColorMap& cm) { this->colorMap = cm; }

private:
	SPHAnisotropicParticleScene* model;
	Scene::PointShaderScene* view;
	Graphics::ColorMap colorMap;
	Mode mode;
};

	}
}