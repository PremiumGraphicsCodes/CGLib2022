#pragma once

#include "IOkCancelView.h"
#include "StringView.h"
#include "ComboBox.h"
#include "BoolView.h"
#include "ColorMapView.h"
#include "../../Crystal/Shape/Volume.h"

namespace Crystal {
	namespace UI {

class IVolAddView : public IOkCancelView
{
public:
	IVolAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addVolume(std::unique_ptr<Shape::Volume<float>> volume);

private:
	StringView nameView;
	ComboBox presenterView;
	ColorMapView colorMapView;
};

	}
}