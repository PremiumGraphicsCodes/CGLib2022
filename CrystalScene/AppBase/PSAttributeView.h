#pragma once

#include "IPopupButton.h"
#include "FloatView.h"
#include "Float4View.h"
#include "StringView.h"
#include "ColorRGBAView.h"

#include "../Scene/ParticleAttribute.h"

namespace Crystal {
	namespace UI {

class PSAttributeView : public IWindow
{
public:
	PSAttributeView(const std::string& name) :
		IWindow(name),
		sizeView("Size", 10.0f),
		colorView("Color", glm::vec4(1,1,1,1))
	{
	}

	void onShow() override
	{
		sizeView.show();
		colorView.show();
	}

	Scene::ParticleAttribute getValue() const {
		Scene::ParticleAttribute attr;
		attr.size = sizeView.getValue();
		attr.color = colorView.getValue();
		return attr;
	}

	void setValue(const Scene::ParticleAttribute& value) {
		this->sizeView.setValue( value.size );
		this->colorView.setValue(value.color);
	}
	

private:
	FloatView sizeView;
	ColorRGBAView colorView;
};

	}
}

