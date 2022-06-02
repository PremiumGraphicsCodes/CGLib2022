#include "SparseVolume.h"
#include <bitset>

using namespace Crystal::Math;
using namespace Crystal::Space;

namespace {
	constexpr long int p1 = 73856093;
	constexpr long int p2 = 19349663;
	constexpr long int p3 = 83492791;
}

template class SparseVolumeNode<bool>;
template class SparseVolumeNode<float>;
template class SparseVolumeNode<double>;

template<typename T>
void SparseVolume<T>::clear()
{
	for (auto& t : table) {
		for (auto c : t) {
			delete c;
		}
	}
	table.clear();
}

template<typename T>
Vector3dd SparseVolume<T>::getPositionAt(const std::array<int, 3>& index) const
{
	const auto x = index[0] * cellLength[0];
	const auto y = index[1] * cellLength[1];
	const auto z = index[2] * cellLength[2];
	return Vector3dd(x, y, z);
}

template<typename T>
SparseVolumeNode<T>* SparseVolume<T>::findNode(const std::array<int, 3>& index) const
{
	const auto nodes = table[ toHash(index) ];
	for (auto n : nodes) {
		const auto ix = n->getIndex();
		if (index == ix) {
			return n;
		}
	}
	return nullptr;
}

template<typename T>
SparseVolumeNode<T>* SparseVolume<T>::createNode(const std::array<int, 3>& index)
{
	const auto pos = getPositionAt(index);
	auto node = new SparseVolumeNode<T>(pos, index);
	const auto i = toHash(index);
	table[i].push_back(node);
	return node;
}

template<typename T>
void SparseVolume<T>::addValue(const std::array<int, 3>& index, const T value)
{
	auto n = findNode(index);
	n->setValue(n->getValue() + value);
}

template<typename T>
T SparseVolume<T>::getValueAt(const std::array<int, 3>& index) const
{
	auto n = findNode(index);
	if(n == nullptr) {
		return 0.0f;
	}
	return n->getValue();
}

template<typename T>
bool SparseVolume<T>::exists(const std::array<int, 3>& index) const
{
	auto node = findNode(index);
	return node != nullptr;
}

template<typename T>
std::array<int, 3> SparseVolume<T>::toIndex(const Vector3df& pos) const
{
	Vector3df p = pos;
	if (p.x > 0.0) {
		p.x = pos.x + cellLength.x * 0.5f;
	}
	else {
		p.x = pos.x - cellLength.x * 0.5f;
	}
	if (p.y > 0.0) {
		p.y = pos.y + cellLength.y * 0.5f;
	}
	else {
		p.y = pos.y - cellLength.y * 0.5f;
	}
	if (p.z > 0.0) {
		p.z = pos.z + cellLength.z * 0.5f;
	}
	else {
		p.z = pos.z - cellLength.z * 0.5f;
	}
	const int ix = static_cast<int>(p[0] / cellLength[0]);
	const int iy = static_cast<int>(p[1] / cellLength[1]);
	const int iz = static_cast<int>(p[2] / cellLength[2]);
	return { ix, iy, iz };
}

template<typename T>
int SparseVolume<T>::toHash(const Vector3df& pos) const
{
	return toHash(toIndex(pos));
}

template<typename T>
int SparseVolume<T>::toHash(const std::array<int, 3>& index) const
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

template<typename T>
Vector3dd SparseVolume<T>::getCellLength() const
{
	return cellLength;
}

template<typename T>
std::list<SparseVolumeNode<T>*> SparseVolume<T>::getNodes() const
{
	std::list<SparseVolumeNode<T>*> nodes;
	for (auto t : table) {
		for (auto n : t) {
			nodes.push_back(n);
		}
	}
	return nodes;
}

template<typename T>
Box3dd SparseVolume<T>::getBoundingBox() const
{
	auto box = Box3dd::createDegeneratedBox();

	const auto nodes = getNodes();
	for (auto n : nodes) {
		box.add( n->getPosition() );
	}
	return box;
}

template class SparseVolume<bool>;
template class SparseVolume<float>;
template class SparseVolume<double>;
