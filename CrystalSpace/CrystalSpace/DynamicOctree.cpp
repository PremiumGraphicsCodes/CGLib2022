#include "DynamicOctree.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

void DynamicOctree::clear()
{
	for (auto c : children) {
		c->clear();
		delete c;
	}
}

Box3dd DynamicOctree::calculateBox(const std::vector<IParticle*>& particles, const float cellLength)
{
	Box3dd b = Box3dd::createDegeneratedBox();
	for (auto p : particles) {
		b.add(p->getPosition());
	}
	const auto maxLength = std::max( std::max(b.getLength().x, b.getLength().y), b.getLength().z );
	const auto l = maxLength / cellLength;
	const auto level = std::max(3.0, std::floor( std::log2(l) + 1.0));
	const auto ll = std::pow(2, level);
	const auto minIndex = ( b.getMin() / (double)cellLength);
	const auto ix = std::floor(minIndex[0]) * cellLength;
	const auto iy = std::floor(minIndex[1]) * cellLength;
	const auto iz = std::floor(minIndex[2]) * cellLength;
	const Vector3dd v1(ix, iy, iz);
	return Box3dd(v1, v1 + ll * cellLength);
}

void DynamicOctree::divide(const float cellLength, const std::vector<IParticle*>& particles)
{
	if (this->bb.getLength().x < cellLength * 4.0) {
		this->particles = particles;
		return;
	}

	for (auto u = 0.0; u < 1.0; u += 0.5) {
		for (auto v = 0.0; v < 1.0; v += 0.5) {
			for (auto w = 0.0; w < 1.0; w += 0.5) {
				const auto v1 = bb.getPosition(u, v, w);
				const auto v2 = bb.getPosition(u + 0.5, v + 0.5, w + 0.5);
				const Box3dd subSpace(v1, v2);
				DynamicOctree* child = new DynamicOctree(subSpace);
				std::vector<IParticle*> inParticles;
				for (auto p : particles) {
					if (subSpace.contains(p->getPosition(), cellLength)) {
						inParticles.push_back(p);
					}
				}
				if (inParticles.empty()) {
					continue;
				}
				child->divide(cellLength, inParticles);
				this->children.push_back(child);
			}
		}
	}
}

std::list<DynamicOctree*> DynamicOctree::toSerialList()
{
	std::list<DynamicOctree*> results;
	results.push_back(this);
	for (auto c : children) {
		/*
		if (c->isEmpty()) {
			continue;
		}
		*/
		auto list = c->toSerialList();
		results.insert(results.end(), list.begin(), list.end());
	}
	return results;
}

std::vector<Volume<double>*> DynamicOctree::toVolumes(const float cellLength)
{
	const auto trees = toSerialList();
	std::vector < Volume<double>* > volumes;
	for (auto t : trees) {
		if (!t->isEmpty()) {
			std::array<size_t, 3> res{ 4, 4, 4 };
			const auto b = t->getBox();
			const auto v1 = b.getMin() - Vector3dd(cellLength);
			const auto v2 = b.getMax() + Vector3dd(cellLength);
			auto v = new Volume<double>(Box3d(v1,v2), res);
			volumes.push_back(v);
		}
	}
	return volumes;
}
