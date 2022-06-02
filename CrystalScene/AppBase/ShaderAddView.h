#pragma once

#include "IOkCancelView.h"
#include "ShaderView.h"

namespace Crystal {
	namespace UI {

class ShaderAddView : public IOkCancelView
{
public:
	ShaderAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void onShow() override;

	void onOk() override;

private:
	ShaderView shader;
};

	}
}
