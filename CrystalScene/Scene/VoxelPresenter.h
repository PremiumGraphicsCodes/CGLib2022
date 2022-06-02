#pragma once

#include "IPresenter.h"
#include "Crystal/Graphics/ColorMap.h"

namespace Crystal {
	namespace Scene {
		class VoxelScene;
		class PointShaderScene;

class VoxelPresenter : public IPresenter
{
public:
	explicit VoxelPresenter(VoxelScene* model);

	void createView(SceneShader* sceneShader) override;

	void removeView(SceneShader* sceneShader) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	PointShaderScene* view;
	VoxelScene* model;
};

	}
}