#include "ParticleSystemScene.h"

#include "ParticleSystemPresenter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

IParticleSystemScene::IParticleSystemScene(const int id, const std::string& name) :
	IShapeScene(id, name)
{}

ParticleSystemScene::ParticleSystemScene() :
	IParticleSystemScene(-1, ""),
	shape(nullptr)
{
	presenter = std::make_unique<ParticleSystemPresenter>(this);
}

ParticleSystemScene::ParticleSystemScene(const int id, const std::string& name, std::unique_ptr<ParticleSystem<ParticleAttribute>> shape) :
	IParticleSystemScene(id, name),
	shape(std::move(shape))
{
	presenter = std::make_unique<ParticleSystemPresenter>(this);
}

Crystal::Math::Box3dd ParticleSystemScene::getBoundingBox() const
{
	return getShape()->getBoundingBox();
}

void ParticleSystemScene::setAttribute(const ParticleAttribute& attribute)
{
	auto particles = getShape()->getParticles();
	for (auto p : particles) {
		p->setAttribute(attribute);
	}
}