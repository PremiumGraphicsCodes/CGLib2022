#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class MaterialScene;
		class MaterialShaderScene;

class MaterialPresenter : public IPresenter
{
public:
	explicit MaterialPresenter(MaterialScene* model);

	void createView(SceneShader* sceneShader) override;

	void removeView(SceneShader* sceneShader) override;

	void updateView() override;

	//SmoothShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	MaterialScene* model;
	MaterialShaderScene* view;
	int index = 0;
};

	}
}