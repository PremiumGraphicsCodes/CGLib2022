#pragma once

#include "IView.h"

#include "Vector3dView.h"
#include "ColorRGBAView.h"
#include "../../Crystal/Graphics/SpotLight.h"

namespace Crystal {
	namespace UI {

class SpotLightView : public IView
{
public:
	explicit SpotLightView(const std::string& name);

	void setValue(const Graphics::SpotLight& value);

	Graphics::SpotLight getValue() const;

public:
	Vector3dView position;
	Vector3dView direction;
	ColorRGBAView ambient;
	ColorRGBAView diffuse;
	ColorRGBAView specular;
};

	}
}