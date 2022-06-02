#pragma once

#include "IView.h"
#include "ComboBox.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class World;
	}
	namespace UI {

class MaterialSelectView : public ComboBox
{
public:
	explicit MaterialSelectView(const std::string& name, Scene::World* world);

	//void setPresenter(Scene::PolygonMeshScene* scene, Scene::World* world);

private:
	//ComboBox materialsView;
};

	}
}