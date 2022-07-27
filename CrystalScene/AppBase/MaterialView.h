#pragma once

#include "IView.h"

#include "Vector3dView.h"

#include "FloatView.h"
#include "Float4View.h"

#include "../../Crystal/Graphics/Material.h"

namespace Crystal {
	namespace Scene {
		class MaterialScene;
	}
	namespace UI {

class MaterialView : public IView
{
public:
	explicit MaterialView(const std::string& name);

	void setValue(const Graphics::Material& m);

	Graphics::Material getValue() const;

public:
	Float4View ambientView;
	Float4View diffuseView;
	Float4View specularView;
	FloatView shininessView;
};
	}
}