#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"
#include "StringView.h"
#include "VertexView.h"

namespace Crystal {
	namespace Shape {
		class Face;
	}
	namespace UI {

class FaceView : public IWindow
{
public:
	explicit FaceView(const std::string& name);

	FaceView(const std::string& name, const Shape::Face& value);

	void onShow() override;

	void setValue(const Shape::Face& value);

private:
	IntView id;
	IntView vertex1;
	IntView vertex2;
	IntView vertex3;
};
	}
}