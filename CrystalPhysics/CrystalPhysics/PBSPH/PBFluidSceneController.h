#pragma once

#include "CrystalScene/Scene/IPresenter.h"

#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"
#include "Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Physics {
		class PBFluidScene;

class PBFluidSceneController : public Scene::IPresenter
{
public:
	explicit PBFluidSceneController(PBFluidScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override {};

	void updateView() override;

	enum class Mode
	{
		Uniform,
		Density,
	};

private:
	PBFluidScene* model;
	Scene::PointShaderScene* view;
	Graphics::ColorMap colorMap;
	Mode mode;

};

	}
}