#pragma once

#include "IPMPresenter.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class LineShaderScene;

class PMWirePresenter : public IPMPresenter
{
public:
	explicit PMWirePresenter(PolygonMeshScene* model);

	void createView(SceneShader* sceneShader) override;

	void removeView(SceneShader* sceneShader) override;

	void updateView() override;

	LineShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	LineShaderScene* view;
};

	}
}