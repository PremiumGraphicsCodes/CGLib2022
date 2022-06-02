#pragma once

#include "IView.h"

#include "../../Crystal/Math/Cylinder3d.h"

#include "Vector3dView.h"
#include "DoubleView.h"

namespace Crystal {
	namespace UI {

class Cylinder3dView : public IView
{
public:
	explicit Cylinder3dView(const std::string& name);

	Math::Cylinder3d getValue() const;

	void setValue(const Math::Cylinder3d& value);

private:
	Vector3dView centerView;
	DoubleView radiusView;
	DoubleView heightView;
};

	}
}