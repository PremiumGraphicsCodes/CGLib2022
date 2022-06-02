#include "IOkCancelView.h"

#include "LightView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class LightAddView : public IOkCancelView
{
public:
	LightAddView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk();

private:
	LightView lightView;
	StringView nameView;
};

	}
}