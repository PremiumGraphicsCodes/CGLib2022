#pragma once

#include "CrystalScene/Scene/IPresenter.h"
#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"

#include "Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Physics {
		class SPHFlameScene;

class SPHFlameScenePresenter : public Scene::IPresenter
{
public:
	explicit SPHFlameScenePresenter(SPHFlameScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override{};

	void updateView() override;

	enum class Mode
	{
		Uniform,
		Temperature,
		Fuel,
	};

	void setMode(const Mode mode) { this->mode = mode; }

private:
	SPHFlameScene* model;
	Scene::PointShaderScene* view;
	Graphics::ColorMap colorMap;
	Mode mode;
};

	}
}