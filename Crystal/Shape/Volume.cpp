#include "Volume.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

template<typename T>
Volume<T>::Volume() :
	box(Box3dd()),
	nodes(2,2,2)
{}

template<typename T>
Volume<T>::Volume(const Math::Box3dd& box, const std::array<size_t, 3>& resolutions) :
	box(box),
	nodes(resolutions[0], resolutions[1], resolutions[2])
{
}

template<typename T>
Volume<T>::Volume(const Math::Box3dd& box, const Util::Array3d<T>& nodes) :
	box(box),
	nodes(nodes)
{}

template<typename T>
Vector3dd Volume<T>::getCellPosition(const size_t i, const size_t j, const size_t k) const
{
	const auto& length = getCellLength();
	const auto cx = length.x * i;
	const auto cy = length.y * j;
	const auto cz = length.z * k;
	return box.getMin() + length * 0.5 + Math::Vector3dd(cx, cy, cz);
}

template<typename T>
std::array<size_t, 3> Volume<T>::getIndexFromPosition(const Vector3dd& position)
{
	const auto p = position - box.getMin();
	const auto length = getCellLength();
	const auto ix = static_cast<size_t>(p.x / length.x);
	const auto iy = static_cast<size_t>(p.y / length.y);
	const auto iz = static_cast<size_t>(p.z / length.z);
	return { ix, iy, iz };
}

template<typename T>
Vector3dd Volume<T>::getCellLength() const
{
	const auto& length = box.getLength();
	const auto& resolutions = nodes.getResolutions();
	const auto dx = length.x / static_cast<double>(resolutions[0]);
	const auto dy = length.y / static_cast<double>(resolutions[1]);
	const auto dz = length.z / static_cast<double>(resolutions[2]);
	return Math::Vector3dd(dx, dy, dz);
}

template class Volume<bool>;
template class Volume<float>;
template class Volume<double>;