#include "TrimCommand.h"
#include "../Scene/World.h"
#include "../Scene/IShapeScene.h"
#include "../Scene/ParticleSystemScene.h"
#include "../../Crystal/Math/Sphere3d.h"

#include "PublicLabel.h"

namespace TrimLabels
{
	PublicLabel TrimCommandLabel = "Trim";
	PublicLabel ShapeIdLabel = "ShapeId";
	PublicLabel SpaceLabel = "Space";
	PublicLabel NewIdLabel = "NewId";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TrimCommand::Args::Args() :
	shapeId(TrimLabels::ShapeIdLabel, -1),
	spheres("Spheres", std::vector<Sphere3dd>())
//	space(::SpaceLabel, Math::Space3d())
{
	add(&shapeId);
	add(&spheres);
};

TrimCommand::Results::Results() :
	newId(TrimLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string TrimCommand::getName()
{
	return TrimLabels::TrimCommandLabel;
}

bool TrimCommand::execute(World* world)
{
	auto shape = world->getScenes()->findSceneById<IShapeScene*>(args.shapeId.getValue());
	if (shape == nullptr) {
		return false;
	}
	Space3d space;
	auto spheres = args.spheres.getValue();
	for (auto& s : spheres) {
		space.add(&s);
	}
	if (shape->getType() == SceneTypeLabels::ParticleSystemScene) {
		auto pss = static_cast<ParticleSystemScene*>(shape);
		auto ps = pss->getShape();
		const auto& particles = ps->getParticles();
		std::vector<Vector3dd> positions;
		for (auto p : particles) {
			const auto& pos = p->getPosition();
			if (space.isInside(pos)) {
				positions.push_back(pos);
			}
		}
		ParticleAttribute attr;
		attr.color = Crystal::Graphics::ColorRGBAf(1.0, 0.0, 0.0, 0.0);
		attr.size = 1.0f;
		auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
		auto newObj = new ParticleSystemScene(world->getNextSceneId(), "Trimmed",std::move(shape));
		world->getScenes()->addScene(newObj);
		results.newId.setValue(newObj->getId());
	}
	return true;
}
