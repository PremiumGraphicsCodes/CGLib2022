#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"
#include "CrystalScene/AppBase/StringView.h"
#include "../CrystalSpace/Voxel.h"

namespace Crystal {
	namespace UI {

class IVoxelAddView : public IOkCancelView
{
public:
	IVoxelAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addVoxel(std::unique_ptr<Space::Voxel> voxel);

private:
	StringView nameView;
};

	}
}