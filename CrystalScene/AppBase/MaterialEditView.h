#pragma once

#include "IEditCancelView.h"
#include "IPopupButton.h"
#include "MaterialView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class MaterialEditView : public IEditCancelView
{
public:
	MaterialEditView(const std::string& name, Scene::World* model, Canvas* canvas);

	void setValue(Scene::MaterialScene* value);

private:
	void onEdit() override;

	IntView idView;
	MaterialView materialView;
	StringView nameView;
};

	}
}
