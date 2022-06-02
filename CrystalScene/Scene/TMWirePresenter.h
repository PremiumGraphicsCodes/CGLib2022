#pragma once

#include "ITMPresenter.h"

namespace Crystal {
	namespace Scene {
		class TriangleMeshScene;
		class LineShaderScene;

class TMWirePresenter : public ITMPresenter
{
public:
	explicit TMWirePresenter(TriangleMeshScene* model);

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