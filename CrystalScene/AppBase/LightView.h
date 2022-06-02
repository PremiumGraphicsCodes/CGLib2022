#pragma once

#include "IView.h"

#include "Vector3dView.h"
#include "ColorRGBAView.h"
#include "../../Crystal/Graphics/PointLight.h"

namespace Crystal {
	namespace UI {

class LightView : public IView
{
public:
	explicit LightView(const std::string& name);

	void setValue(const Graphics::PointLight& value);

	Graphics::PointLight getValue() const;

public:
	Vector3dView position;
	ColorRGBAView ambient;
	ColorRGBAView diffuse;
	ColorRGBAView specular;
};

	}
}