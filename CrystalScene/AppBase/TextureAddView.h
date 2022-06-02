#include "IOkCancelView.h"

#include "FileOpenView.h"

namespace Crystal {
	namespace UI {

class TextureAddView : public IOkCancelView
{
public:
	TextureAddView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk();

private:
	//TextureView image;
	FileOpenView filePathView;
	StringView nameView;
};

	}
}