#pragma once

#include "IView.h"

#include "Vector3dView.h"

#include "../../Crystal/Math/Quad3d.h"

namespace Crystal {
	namespace UI {

class Quad3dView : public IView
{
public:
	explicit Quad3dView(const std::string& name);

	Math::Quad3d getValue() const;

private:
	Vector3dView originView;
	Vector3dView uvecView;
	Vector3dView vvecView;
};

	}
}