#pragma once

#include "IOkCancelView.h"

#include "MaterialView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class MaterialAddView : public IOkCancelView
{
public:
	MaterialAddView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	MaterialView materialView;
	StringView nameView;
};

	}
}