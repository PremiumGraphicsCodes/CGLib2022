#include "VoxelScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;

VoxelScene::VoxelScene(const int id, const std::string& name, std::unique_ptr<Volume<bool>> shape) :
	IShapeScene(id, name),
	shape(std::move(shape))
{
	presenter = std::make_unique<VoxelPresenter>(this);
}
