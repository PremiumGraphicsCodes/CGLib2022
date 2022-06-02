#pragma once

#include "IWFAddView.h"
#include "IntView.h"
#include "Ellipsoid3dView.h"

namespace Crystal {
	namespace UI {

class WFEllipsoidView : public IWFAddView
{
public:
	WFEllipsoidView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	IntView unumView;
	IntView vnumView;
	Ellipsoid3dView ellipsoidView;
};

	}
}