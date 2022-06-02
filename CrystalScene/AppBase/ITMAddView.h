#pragma once

#include "IOkCancelView.h"
#include "StringView.h"
//#include "TMPresenterView.h"
#include <memory>

namespace Crystal {
	namespace Shape {
		class TriangleMesh;
	}
	namespace UI {

class ITMAddView : public IOkCancelView
{
public:
	ITMAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addTriangleMesh(std::unique_ptr<Shape::TriangleMesh> shape);

private:
	StringView nameView;
	//TMPresenterView presenterView;
};

	}
}