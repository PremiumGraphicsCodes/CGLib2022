#pragma once

#include "../IMVPFluidScenePresenter.h"
#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"

#include "Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Physics {
		class IMVPFluidScene;

class MVPFluidScenePresenter : public IMVPFluidScenePresenter
{
public:
	explicit MVPFluidScenePresenter(IMVPFluidScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override {};

	void updateView() override;

	enum class Mode
	{
		Uniform,
		Density,
	};

	void setMode(const Mode mode) { this->mode = mode; }

private:
	IMVPFluidScene* model;
	Scene::PointShaderScene* view;
	Graphics::ColorMap colorMap;
	Mode mode;
};

	}
}