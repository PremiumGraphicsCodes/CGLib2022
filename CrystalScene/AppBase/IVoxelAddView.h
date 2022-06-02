#pragma once

#include "IOkCancelView.h"
#include "StringView.h"
#include "ComboBox.h"
#include "BoolView.h"
#include "ColorMapView.h"
#include "../../Crystal/Shape/Volume.h"

namespace Crystal {
	namespace UI {

class IVoxelAddView : public IOkCancelView
{
public:
	IVoxelAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addVoxel(std::unique_ptr<Shape::Volume<bool>> voxel);

private:
	StringView nameView;
	ComboBox presenterView;
	ColorMapView colorMapView;
};

	}
}