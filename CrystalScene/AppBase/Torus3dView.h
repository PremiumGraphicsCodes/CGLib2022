#pragma once

#include "IWindow.h"

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Torus3d.h"

#include "Vector3dView.h"
#include "DoubleView.h"

namespace Crystal {
	namespace UI {

class TorusView : public IWindow
{
public:
	explicit TorusView(const std::string& name) :
		IWindow(name),
		center("Center", Math::Vector3dd(0,0,0)),
		bigRadius("BigRadius", 1.0),
		smallRadius("SmallRadius", 0.1)
	{
	}

	void onShow() override
	{
		center.show();
		bigRadius.show();
		smallRadius.show();
	}

	Math::Torus3d getValue() const { return Math::Torus3d(center.getValue(), bigRadius.getValue(), smallRadius.getValue()); }

private:
	Vector3dView center;
	DoubleView bigRadius;
	DoubleView smallRadius;
};

	}
}