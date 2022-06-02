#pragma once

#include <utility>

namespace Crystal {
	namespace Space {

class LinearOctreeIndex
{
public:
	explicit LinearOctreeIndex(const unsigned int index1d) :
		index1d(index1d)
	{}

	LinearOctreeIndex(const unsigned int level, const unsigned int number);

	std::pair<unsigned int, unsigned int> getLevelAndNumber() const;

	LinearOctreeIndex getParentIndex() const;

	//unsigned int getNumber() const;

	unsigned int getIndex1d() const;

	bool operator==(const LinearOctreeIndex& rhs) const { return this->index1d == rhs.index1d; }

	bool operator<(const LinearOctreeIndex& rhs) const { return this->index1d < rhs.index1d; }

private:
	unsigned int index1d;
};

	}
}