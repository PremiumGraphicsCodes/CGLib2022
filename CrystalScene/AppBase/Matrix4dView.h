#pragma once

#include "IView.h"

#include "../../Crystal/Math/Matrix4d.h"
#include "Double4View.h"

namespace Crystal {
	namespace UI {

class Matrix4dView : public IView
{
public:
	Matrix4dView(const std::string& name, const Math::Matrix4dd& value);

	void setValue(const Math::Matrix4dd& value);

	Math::Matrix4dd getValue() const;

private:
	Double4View row1View;
	Double4View row2View;
	Double4View row3View;
	Double4View row4View;
};

	}
}