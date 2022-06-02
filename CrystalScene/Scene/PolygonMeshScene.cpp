#include "PolygonMeshScene.h"

//#include "PMWirePresenter.h"
#include "PMSmoothPresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

PolygonMeshScene::PolygonMeshScene() :
	IShapeScene(-1),
	shape(nullptr)
{
	presenter = std::make_unique<PMSmoothPresenter>(this);
}

PolygonMeshScene::PolygonMeshScene(const int id, const std::string& name, std::unique_ptr<PolygonMesh> shape) :
	IShapeScene(id, name),
	shape(std::move(shape))
{
	presenter = std::make_unique<PMSmoothPresenter>(this);
}

PolygonMeshScene::~PolygonMeshScene()
{

}

Box3dd PolygonMeshScene::getBoundingBox() const
{
	return getShape()->getBoundingBox();
}