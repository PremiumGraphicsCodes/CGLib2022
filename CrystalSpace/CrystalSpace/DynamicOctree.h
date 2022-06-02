#pragma once

#include <vector>
#include <list>

#include "Crystal/Math/Box3d.h"
#include "Crystal/Shape/IParticle.h"
#include "Crystal/Shape/Volume.h"

namespace Crystal {
	namespace Space {

class DynamicOctree
{
public:
	explicit DynamicOctree(const Math::Box3dd& bb) :
		bb(bb)
	{}

	void clear();

	static Math::Box3dd calculateBox(const std::vector<Shape::IParticle*>& particles, const float cellLength);

	void add(Shape::IParticle* p) { this->particles.push_back(p); }

	void divide(const float cellLength, const std::vector<Shape::IParticle*>& particles);

	std::list<DynamicOctree*> toSerialList();

	std::vector<Shape::Volume<double>*> toVolumes(const float cellLength);

	bool isEmpty() const { return particles.empty(); }

	Math::Box3dd getBox() const { return bb; }

private:
	Math::Box3dd bb;
	std::vector<Shape::IParticle*> particles;
	std::list<DynamicOctree*> children;
};

	}
}