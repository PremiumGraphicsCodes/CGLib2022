#pragma once

#include "../Scene/ParticleSystemScene.h"
#include "../Scene/World.h"

#include "IEditCancelView.h"
#include "IntView.h"
#include "PSAttributeView.h"
#include "Canvas.h"

#include "ComboBox.h"

namespace Crystal {
	namespace UI {

class ParticleSystemEditView : public IEditCancelView
{
public:
	ParticleSystemEditView(const std::string& name, Scene::World* world, Canvas* canvas);

	void setValue(Scene::ParticleSystemScene* value);

private:
	void onEdit();

private:
	IntView idView;
	PSAttributeView attributeView;
	ComboBox presenterView;
};

	}
}
