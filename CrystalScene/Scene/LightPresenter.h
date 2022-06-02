#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class LightScene;
		class MaterialShaderScene;

class LightPresenter : public IPresenter
{
public:
	explicit LightPresenter(LightScene* model);

	void createView(SceneShader* sceneShader) override;

	void removeView(SceneShader* sceneShader) override;

	void updateView() override;

	//SmoothShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	LightScene* model;
	MaterialShaderScene* view;
	int index = 0;
};

	}
}