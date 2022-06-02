#pragma once

#include "IPanel.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class IEditCancelView : public IPanel
{
public:
	IEditCancelView(const std::string& name, Scene::World* world, Canvas* canvas) :
		IPanel(name, world, canvas),
		edit("Edit"),
		cancel("Cancel")
	{
		edit.setFunction([=]() { onEdit(); });
		cancel.setFunction([=]() { onCancel(); });
	}

	virtual ~IEditCancelView() {}

protected:
	virtual void onShow() {
		for (auto c : children) {
			c->show();
		}
		edit.show();
		cancel.show();
	}

	virtual void onEdit() = 0;

	virtual void onCancel() {};

private:
	Button edit;
	Button cancel;
};

	}
}