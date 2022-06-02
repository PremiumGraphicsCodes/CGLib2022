#pragma once

#include "IOkCancelView.h"
#include "StringView.h"
#include "ColorRGBAView.h"

#include "../../Crystal/Shape/Solid.h"

namespace Crystal {
	namespace UI {

class ISolidAddView : public IOkCancelView
{
public:
	ISolidAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addSolid(std::unique_ptr<Shape::Solid> solid);

private:
	ColorRGBAView colorView;
	StringView nameView;
};

	}
}