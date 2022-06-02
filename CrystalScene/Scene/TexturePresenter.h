#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class TextureScene;
		class MaterialShaderScene;

class TexturePresenter : public IPresenter
{
public:
	explicit TexturePresenter(TextureScene* model);

	void createView(SceneShader* sceneShader) override;

	void removeView(SceneShader* sceneShader) override;

	void updateView() override;

	//SmoothShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	TextureScene* model;
	MaterialShaderScene* view;
	int index = 0;
};

	}
}