#pragma once

#include "IView.h"

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Cone3d.h"

#include "Vector3dView.h"
#include "DoubleView.h"

namespace Crystal {
	namespace UI {

class Cone3dView : public IView
{
public:
	explicit Cone3dView(const std::string& name);

	Math::Cone3d getValue() const;

	void setValue(const Math::Cone3d& value);

private:
	Vector3dView bottomView;
	DoubleView radiusView;
	DoubleView heightView;
};

	}
}
