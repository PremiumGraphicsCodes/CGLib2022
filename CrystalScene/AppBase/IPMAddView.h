#pragma once

#include "IOkCancelView.h"
#include "StringView.h"
#include "PMPresenterView.h"
#include "MaterialSelectView.h"


namespace Crystal {
	namespace Shape {
		class PolygonMeshBuilder;
	}
	namespace UI {

class IPMAddView : public IOkCancelView
{
public:
	IPMAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addPolygonMesh(const Shape::PolygonMeshBuilder& builder);

private:
	StringView nameView;
	MaterialSelectView materialView;
	PMPresenterView presenterView;
};

	}
}