#pragma once

#include "IView.h"

#include "Vector3dView.h"
#include "../../Crystal/Math/Plane3d.h"

namespace Crystal {
	namespace UI {

class Plane3dView : public IView
{
public:
	explicit Plane3dView(const std::string& name);

	Math::Plane3d getValue() const;

	void setValue(const Math::Plane3d& value);

private:
	Vector3dView originView;
	Vector3dView normalView;
};

	}
}