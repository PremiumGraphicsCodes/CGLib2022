#include "CompactSpaceHash3d.h"

#include <bitset>

#include "../../Crystal/Shape/IParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	constexpr long int p1 = 73856093;
	constexpr long int p2 = 19349663;
	constexpr long int p3 = 83492791;
}

CompactSpaceHash3d::CompactSpaceHash3d()
{
}

CompactSpaceHash3d::CompactSpaceHash3d(const double divideLength, const int tableSize) :
	divideLength(divideLength),
	table(tableSize),
	zCurve()
{
}

CompactSpaceHash3d::~CompactSpaceHash3d()
{
	clear();
}

void CompactSpaceHash3d::setup(const double divideLength, const int tableSize)
{
	this->divideLength = divideLength;
	this->table.resize(tableSize);
}

void CompactSpaceHash3d::clear()
{
	for (auto cell : cells) {
		cell->particles.clear();
		delete cell;
	}
	cells.clear();

	for (auto& t : table) {
		/*
		for (auto& tt : t) {
			tt->particles.clear();
		}
		*/
		t.clear();
	}
	table.clear();
}

void CompactSpaceHash3d::add(IParticle* particle)
{
	const auto& index = toIndex(particle->getPosition());
	const auto hashIndex = toHash(index);
	const auto cellId = toZIndex(index);

	auto& cells = table[hashIndex];
	auto iter = std::find_if(cells.begin(), cells.end(), [cellId](CompactSpaceCell* cell) {
		return cell->cellId == cellId;
	});
	if (iter == cells.end()) {
		auto cell = new CompactSpaceCell();
		cell->index = index;
		cell->cellId = cellId;
		cell->particles.reserve(64);
		cell->particles.push_back(particle);
		this->cells.push_back(cell);
		cells.push_back(cell);
	}
	else {
		(*iter)->particles.push_back(particle);
	}
}

void CompactSpaceHash3d::remove(IParticle* particle)
{
	const auto& index = toIndex(particle->getPosition());
	const auto hashIndex = toHash(index);
	const auto cellId = toZIndex(index);

	auto& cells = table[hashIndex];
	auto iter = std::find_if(cells.begin(), cells.end(), [cellId](CompactSpaceCell* cell) { return cell->cellId == cellId; });
	assert(iter != cells.end());
	auto& ps = (*iter)->particles;
	ps.erase(std::remove(ps.begin(), ps.end(), particle), ps.end());
}

bool CompactSpaceHash3d::has(IParticle* particle)
{
	const auto& index = toIndex(particle->getPosition());
	const auto hashIndex = toHash(index);
	const auto cellId = toZIndex(index);

	auto& cells = table[hashIndex];
	auto iter = std::find_if(cells.begin(), cells.end(), [cellId](CompactSpaceCell* cell) { return cell->cellId == cellId; });
	return iter != cells.end();
}

std::vector<IParticle*> CompactSpaceHash3d::findNeighbors(IParticle* particle)
{
	const auto position = particle->getPosition();

	const auto index = toIndex(position);

	std::vector<IParticle*> neighbors;
	neighbors.reserve(64);

	for (int i = - 1; i <= 1; ++i) {
		for (int j = - 1; j <= 1; ++j) {
			for (int k = -1; k <= 1; ++k) {
				std::array<int, 3> ix{ i + index[0],j + index[1],k + index[2] };
				const auto hash = toHash(ix);
				const auto& cells = table[hash];
				const auto cellId = toZIndex(ix);
				auto iter = std::find_if(cells.begin(), cells.end(), [cellId](CompactSpaceCell* cell) {
					return cell->cellId == cellId;
				});
				if (iter == cells.end()) {
					continue;
				}
				const auto& particles = (*iter)->particles;
				for (auto p : particles) {
					if (p == particle) {
						continue;
					}
					const double d2 = Math::getDistanceSquared(p->getPosition(), particle->getPosition());
					if (d2 < divideLength * divideLength) {
						neighbors.push_back(p);
					}
				}
			}
		}
	}
	return neighbors;
}

std::vector<IParticle*> CompactSpaceHash3d::findNeighbors(const Vector3dd& position)
{
	const auto index = toIndex(position);

	std::vector<IParticle*> neighbors;
	neighbors.reserve(64);

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			for (int k = -1; k <= 1; ++k) {
				std::array<int, 3> ix{ i + index[0],j + index[1],k + index[2] };
				const auto hash = toHash(ix);
				const auto& cells = table[hash];
				const auto cellId = toZIndex(ix);
				auto iter = std::find_if(cells.begin(), cells.end(), [cellId](CompactSpaceCell* cell) {
					return cell->cellId == cellId;
				});
				if (iter == cells.end()) {
					continue;
				}
				const auto& particles = (*iter)->particles;
				for (auto p : particles) {
					const double d2 = Math::getDistanceSquared(p->getPosition(), position);
					if (d2 < divideLength * divideLength) {
						neighbors.push_back(p);
					}
				}
			}
		}
	}
	return neighbors;
}

std::vector<IParticle*> CompactSpaceHash3d::find(const Math::Vector3dd& positions) const
{
	return find(toIndex(positions));
}

std::vector<IParticle*> CompactSpaceHash3d::find(const std::array<int,3>& index) const
{
	const auto hash = toHash(index);
	const auto& cells = table[hash];
	const auto cellId = toZIndex(index);
	auto iter = std::find_if(cells.begin(), cells.end(), [cellId](CompactSpaceCell* cell) { return cell->cellId == cellId; });
	if (iter == cells.end()) {
		return {};
	}
	return (*iter)->particles;
}

std::array<int, 3> CompactSpaceHash3d::toIndex(const Vector3df& pos) const
{
	const auto ix = static_cast<int>((pos[0]) / divideLength);
	const auto iy = static_cast<int>((pos[1]) / divideLength);
	const auto iz = static_cast<int>((pos[2]) / divideLength);
	return { ix, iy, iz };
}

Vector3df CompactSpaceHash3d::toPosition(const std::array<int, 3>& index) const
{
	const auto x = divideLength * index[0];
	const auto y = divideLength * index[1];
	const auto z = divideLength * index[2];
	return Vector3df(x, y, z);
}

unsigned int CompactSpaceHash3d::toHash(const Vector3df& pos) const
{
	return toHash(toIndex(pos));
}

unsigned int CompactSpaceHash3d::toHash(const std::array<int, 3>& index) const
{
	std::bitset<32> x = index[0] * p1;
	std::bitset<32> y = index[1] * p2;
	std::bitset<32> z = index[2] * p3;
	//assert(x >= 0);
	//assert(y >= 0);
	//assert(z >= 0);
	const auto value = (x ^ y ^ z).to_ulong();
	return value % table.size();
}

unsigned int CompactSpaceHash3d::toZIndex(const std::array<int, 3>& index) const
{
	return zCurve.encode({ (unsigned int)index[0], (unsigned int)index[1], (unsigned int)index[2] });
}

std::array<unsigned int, 3> CompactSpaceHash3d::fromZIndex(unsigned int index) const
{
	return zCurve.decode(index);
}

bool CompactSpaceHash3d::isEmpty(const Vector3df& pos) const
{
	const auto pts = find( toIndex(pos) );
	return pts.empty();
}
