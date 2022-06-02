#pragma once

#include "IWireFramePresenter.h"

//#include "LineShaderScene.h"

namespace Crystal {
	namespace Scene {
		class WireFrameScene;
		class LineShaderScene;

class WireFramePresenter : public IWireFramePresenter
{
public:
	explicit WireFramePresenter(WireFrameScene* model);

	void createView(SceneShader* sceneShader) override;

	void removeView(SceneShader* sceneShader) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	//WireFrameScene* model;
	LineShaderScene* view;
	LineShaderScene* parentIdView;
};

	}
}