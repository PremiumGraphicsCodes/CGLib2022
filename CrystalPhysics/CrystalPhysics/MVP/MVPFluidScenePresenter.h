#pragma once

#include "CrystalScene/Scene/IPresenter.h"
#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"

#include "Crystal/Graphics/ColorMap.h"

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