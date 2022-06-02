#pragma once

#include "IWindow.h"
#include "FloatView.h"
#include "ColorRGBAView.h"

#include "../Scene/WireFrameAttribute.h"

namespace Crystal {
	namespace UI {

class WFAttributeView : public IWindow
{
public:
	explicit WFAttributeView(const std::string& name);

	void onShow() override;

	Scene::WireFrameAttribute getValue() const;

private:
	FloatView width;
	ColorRGBAView color;
	//StringView nameView;
};

	}
}

