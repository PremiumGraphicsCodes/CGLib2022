#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IParticle.h"
#include <array>

namespace Crystal {
	namespace Space {

class IndexedParticle
{
public:
	IndexedParticle() :
		particle(nullptr)
	{}

	IndexedParticle(Shape::IParticle* particle) :
		particle(particle)
	{
	}

public:
	void setGridID(const float effectLength);

	Math::Vector3df getPosition() const { return particle->getPosition(); }

	static int toGridId(const Math::Vector3df pos, const float effectLength);

	static std::array<int, 3> toIndex(const Math::Vector3df pos, const float effectLength);

	int getGridID() const { return gridID; }

	bool operator<(const IndexedParticle& rhs) {
		return this->getGridID() < rhs.getGridID();
	}

	Shape::IParticle* getParticle() const { return particle; }

private:
	static int toIdX(std::array<int, 3> index);

private:
	Shape::IParticle* particle;
	int gridID;
};

	}
}