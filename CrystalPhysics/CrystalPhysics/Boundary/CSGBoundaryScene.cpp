#include "CSGBoundaryScene.h"
#include "CSGBoundaryScenePresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

CSGBoundaryScene::CSGBoundaryScene(const int id, const std::string& name) :
	IScene(id, name)
{
	this->controller = std::make_unique<CSGBoundaryScenePresenter>(this);
}

CSGBoundaryScene::~CSGBoundaryScene()
{
}

IPresenter* CSGBoundaryScene::getPresenter()
{
	return controller.get();
}

Box3dd CSGBoundaryScene::getBoundingBox() const
{
	if (boxes.empty()) {
		return Box3dd::createDegeneratedBox();
	}
	Box3dd bb(boxes.front());
	for (auto b : boxes) {
		bb.add(b);
	}
	return bb;
}