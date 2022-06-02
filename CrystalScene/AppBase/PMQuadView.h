#pragma once

#include "IPMAddView.h"

#include "Quad3dView.h"

namespace Crystal {
	namespace UI {

class PMQuadView : public IPMAddView
{
public:
	PMQuadView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Quad3dView quadView;
};

	}
}
