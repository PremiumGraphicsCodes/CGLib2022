#pragma once

#include "IParticleSystem.h"

#include "../Math/Box3d.h"

#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

template<typename Attr>
class ParticleSystem : public IParticleSystem
{
public:
	ParticleSystem() {}

	ParticleSystem(const std::vector<Math::Vector3dd>& positions, const Attr& attr)
	{
		for (const auto& p : positions) {
			particles.push_back(new Particle<Attr>(p, attr));
		}
	}

	~ParticleSystem() {
		clear();
	}

	void clear() {
		for (auto p : particles) {
			delete p;
		}
		particles.clear();
	}

	void add(const Math::Vector3dd& position, const Attr& attr) {
		particles.push_back(new Particle<Attr>(position, attr));
	}

	void move(const Math::Vector3dd& v) {
		for (auto p : particles) {
			p->move(v);
		}
	}

	void transform(const Math::Matrix3dd& m) {
		for (auto p : particles) {
			p->transform(m);
		}
	}

	void transform(const Math::Matrix4dd& m) {
		for (auto p : particles) {
			p->transform(m);
		}
	}

	std::vector<Particle<Attr>*>& getParticles() { return particles; }

	std::vector<Particle<Attr>*> getParticles() const { return particles; }

	std::vector<IParticle*> getIParticles() const override
	{
		std::vector<IParticle*> ps;
		for (auto p : particles) {
			ps.push_back(p);
		}
		return ps;
	}

	std::vector<Math::Vector3dd> getPositions() const override
	{
		std::vector<Math::Vector3dd> positions;
		for (const auto& p : particles) {
			positions.push_back(p->getPosition());
		}
		return positions;
	}

	Math::Box3dd getBoundingBox() const
	{
		if (particles.empty()) {
			return Math::Box3dd::createDegeneratedBox();
		}
		Math::Box3dd bb(particles.front()->getPosition());
		for (auto p : particles) {
			bb.add(p->getPosition());
		}
		return bb;
	}

	void resize(int newCount, Attr attr)
	{
		for (int i = particles.size(); i < newCount; ++i) {
			particles.push_back(new Particle<Attr>(Math::Vector3dd(0,0,0), attr));
		}
	}

	size_t getSize() const { return particles.size(); }

private:
	std::vector<Particle<Attr>*> particles;
};

	}
}
