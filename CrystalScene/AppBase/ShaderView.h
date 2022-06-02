#pragma once

#include "IPanel.h"
#include <string>

namespace Crystal {
	namespace UI {

class ShaderView : public IPanel
{
public:
	ShaderView(const std::string& name, Scene::World* model, Canvas* canvas);

	void onShow() override;

	//void setValue(const Scene::IRenderer& scene);

private:
	std::string vsSource;
	std::string fsSource;
};

	}
}