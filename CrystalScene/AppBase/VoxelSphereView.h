#pragma once

#include "IVoxelAddView.h"
#include "Box3dView.h"

namespace Crystal {
	namespace UI {

class VoxelSphereView : public IVoxelAddView
{
public:
	VoxelSphereView(const std::string& name, Scene::World* world, Canvas* canvas);

	void onOk() override;

private:
	Box3dView boxView;
	IntView resolutionView;
};

	}
}