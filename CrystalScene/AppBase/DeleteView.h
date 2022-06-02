#pragma once

#include "IView.h"
#include "Canvas.h"

#include "IOkCancelView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class DeleteView : public IOkCancelView
{
public:
	DeleteView(const std::string& name, Scene::World* model, Canvas* canvas);

	void onOk() override;

private:
	IntView idView;
};
	}
}