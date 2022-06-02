#pragma once

#include "IView.h"
#include "Vector3dView.h"
//#include "DoubleView.h"
#include "../../Crystal/Math/Ellipsoid3d.h"

namespace Crystal {
	namespace UI {

class Ellipsoid3dView : public IView
{
public:
	explicit Ellipsoid3dView(const std::string& name);

	Math::Ellipsoid3d getValue() const;

	void setValue(const Math::Ellipsoid3d& value);

private:
	Vector3dView center;
	Vector3dView uvec;
	Vector3dView vvec;
	Vector3dView wvec;
};

	}
}

