#include "VolumeScene.h"

#include "../../Crystal/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;

VolumeScene::VolumeScene(const int id, const std::string& name, std::unique_ptr<Volume<float>> shape) :
	IShapeScene(id, name),
	shape(std::move(shape))
{
	presenter = std::make_unique<VolumePresenter>(this);
}
