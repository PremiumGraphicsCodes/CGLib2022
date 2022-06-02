#pragma once

#include "IOkCancelView.h"
#include "WFAttributeView.h"
#include "StringView.h"
#include "../../Crystal/Shape/WireFrameEdge.h"

namespace Crystal {
	namespace UI {

class IWFAddView : public IOkCancelView
{
public:
	IWFAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addWireFrame(const std::vector<Math::Vector3dd>& positions, const std::vector<Shape::WireFrameEdge>& edges);

private:
	WFAttributeView attributeView;
	StringView nameView;
};

	}
}