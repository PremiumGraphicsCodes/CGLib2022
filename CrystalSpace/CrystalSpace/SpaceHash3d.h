#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include <list>
#include <functional>
#include <array>

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Space {

class SpaceHash3d : private UnCopyable
{
public:
	SpaceHash3d(const double divideLength, const int tableSize);

	//void add(const Shape::IParticleSystem& particles);

	void add(Shape::IParticle* particle);

	void solveInteractions(Shape::IParticle* particle, const std::function<void(Shape::IParticle*, Shape::IParticle*)>& func);

	std::vector<Shape::IParticle*> getParticles(const Math::Vector3df& position);

	bool isEmpty(const Math::Vector3df& pos) const;

private:
	std::vector<std::list<Shape::IParticle*>> table;

	int toHash(const Math::Vector3df& pos) const;

	int toHash(const std::array<int, 3>& index) const;

	std::array<int, 3> toIndex(const Math::Vector3df& pos) const;

	const double divideLength;
};

	}
}