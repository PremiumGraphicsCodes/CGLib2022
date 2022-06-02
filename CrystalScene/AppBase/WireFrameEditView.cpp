#include "WireFrameEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

WireFrameEditView::WireFrameEditView(const std::string& name, World* repository, Canvas* canvas) :
	IWindow(name),
	//wire("WireFrame"),
	idView("Id"),
	nameView("Name")
{
	add(&idView);
	add(&nameView);
}

void WireFrameEditView::onShow()
{
	//wire.show();
	idView.show();
	nameView.show();
}

void WireFrameEditView::setValue(WireFrameScene* value)
{
	//wire.setValue(value);
	idView.setValue(value->getId());
	nameView.setValue(value->getName());
}