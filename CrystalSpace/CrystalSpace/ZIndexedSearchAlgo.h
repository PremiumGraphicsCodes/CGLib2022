#pragma once

#include "../../Crystal/Math/Vector3d.h"

#include "../../Crystal/Util/UnCopyable.h"

#include "ZOrderCurve3d.h"

#include <vector>
#include <list>

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Space {

class ZIndexedParticle
{
public:
	ZIndexedParticle(const unsigned int zIndex, const Math::Vector3dd& position) :
		zIndex(zIndex),
		position(position)
	{}

	bool operator<(const ZIndexedParticle& rhs) const {
		return this->zIndex < rhs.zIndex;
	}

	/*
	bool operator==(const ZIndexedParticle& rhs) {
		return this->zIndex == rhs.zIndex;
	}
	*/

	Math::Vector3dd getPosition() { return position; }

	int index;

private:
	unsigned int zIndex;
	Math::Vector3dd position;
};

class ZIndexedSearchAlgo : private UnCopyable
{
public:
	explicit ZIndexedSearchAlgo(const double searchRadius, const Math::Vector3dd& minPosition);

	void add(const Math::Vector3dd& position);

	void sort();

	std::list<int> findNeighbors(const Math::Vector3dd& position);

	std::array<unsigned int, 3> toIndex(const Math::Vector3dd& position) const;

private:
	double searchRadius;
	Math::Vector3dd minPosition;
	std::vector<ZIndexedParticle> points;
	ZOrderCurve3d curve;
};
	}
}