#include "FaceView.h"

#include "../../Crystal/Shape/Face.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

FaceView::FaceView(const std::string& name) :
	IWindow(name),
	id("Id"),
	vertex1("Vertex1"),
	vertex2("Vertex2"),
	vertex3("Vertex3")
{
}

FaceView::FaceView(const std::string& name, const Face& face) :
	IWindow(name),
	id("Id", face.getId()),
	vertex1("Vertex1", face.getV1()),
	vertex2("Vertex2", face.getV2()),
	vertex3("Vertex3", face.getV3())
{
	setValue(face);
}

void FaceView::onShow()
{
	id.show();
	vertex1.show();
	vertex2.show();
	vertex3.show();
}

void FaceView::setValue(const Face& value)
{
	id.setValue(value.getId());
	vertex1.setValue(value.getV1());
	vertex2.setValue(value.getV2());
	vertex3.setValue(value.getV3());
}
