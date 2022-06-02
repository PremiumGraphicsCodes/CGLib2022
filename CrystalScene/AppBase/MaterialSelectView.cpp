#include "MaterialSelectView.h"

#include "../Scene/World.h"
#include "MaterialSelectView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialSelectView::MaterialSelectView(const std::string& name, World* world) :
	ComboBox(name)
{
	const auto materials = world->getScenes()->findScenes(SceneTypeLabels::MaterialScene);
	for (auto m : materials) {
		add(m->getName());
	}
	setSelected(materials.front()->getName());
}
