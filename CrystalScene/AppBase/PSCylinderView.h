#include "IPSAddView.h"

#include "Cylinder3dView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSCylinderView : public IPSAddView
{
public:
	PSCylinderView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Cylinder3dView cylinderView;
	IntView countView;
};

	}
}