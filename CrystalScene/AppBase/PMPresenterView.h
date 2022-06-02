#pragma once

#include "ComboBox.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class World;
	}
	namespace UI {

class PMPresenterView : public ComboBox
{
public:
	explicit PMPresenterView(const std::string& name);

	void setPresenter(Scene::PolygonMeshScene* scene, Scene::World* world);

private:
};
	}
}