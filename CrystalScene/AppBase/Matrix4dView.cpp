#include "Matrix4dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Matrix4dView::Matrix4dView(const std::string& name, const Matrix4dd& value) :
	IView(name),
	row1View("Row1"),
	row2View("Row2"),
	row3View("Row3"),
	row4View("Row4")
{
	setValue(value);

	add(&row1View);
	add(&row2View);
	add(&row3View);
	add(&row4View);
}

void Matrix4dView::setValue(const Matrix4dd& value)
{
	row1View.setValue(value[0]);
	row2View.setValue(value[1]);
	row3View.setValue(value[2]);
	row4View.setValue(value[3]);
}

Matrix4dd Matrix4dView::getValue() const
{
	return Matrix4dd
	(
		row1View.getValue(),
		row2View.getValue(),
		row3View.getValue(),
		row4View.getValue()
	);
}
