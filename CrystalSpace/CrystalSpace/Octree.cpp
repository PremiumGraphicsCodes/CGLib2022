#include "Octree.h"
#include "Overlap.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

Octree::Octree(const Box3dd& space, const int level) :
	space(space),
	level(level)
{}

void Octree::add(IOctreeItem* item)
{
	if (Overlap::overlap(this->space, item->getTriangle())) {
		this->items.push_back(item);
		if (children.empty() && level < 4) {
			createChildren();
		}
		for (auto c : children) {
			c->add(item);
		}
	}
}

void Octree::createChildren()
{
	for (auto u = 0.0; u < 1.0; u+=0.5) {
		for (auto v = 0.0; v < 1.0; v+=0.5) {
			for (auto w = 0.0; w < 1.0; w+=0.5) {
				const auto v1 = space.getPosition(u, v, w);
				const auto v2 = space.getPosition(u + 0.5, v + 0.5, w + 0.5);
				const Box3dd subSpace(v1, v2);
				children.push_back(new Octree(subSpace, level+1));
			}
		}
	}
}

bool Octree::isEmpty() const
{
	return items.empty();
}

std::list<Octree*> Octree::toSerialList()
{
	std::list<Octree*> results;
	results.push_back(this);
	for (auto c : children) {
		if (c->isEmpty()) {
			continue;
		}
		auto list = c->toSerialList();
		results.insert(results.end(), list.begin(), list.end());
	}
	return results;
}
