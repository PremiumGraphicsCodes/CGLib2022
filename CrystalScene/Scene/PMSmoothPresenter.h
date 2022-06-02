#pragma once

#include "IPMPresenter.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class SmoothShaderScene;
		class TriangleShaderScene;

class PMSmoothPresenter : public IPMPresenter
{
public:
	explicit PMSmoothPresenter(PolygonMeshScene* model);

	void createView(SceneShader* sceneShader) override;

	void removeView(SceneShader* sceneShader) override;

	void updateView() override;

	SmoothShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	SmoothShaderScene* view;
	TriangleShaderScene* parentIdView;
};

	}
}