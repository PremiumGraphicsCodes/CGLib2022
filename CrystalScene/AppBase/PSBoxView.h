#pragma once

#include "IPSAddView.h"

#include "Box3dView.h"
#include "DoubleView.h"
#include "BoolView.h"

namespace Crystal {
	namespace UI {

class PSBoxView : public IPSAddView
{
public:
	PSBoxView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Box3dView boxView;
	DoubleView divideLengthView;
};

	}
}