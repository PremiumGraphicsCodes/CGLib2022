#include "UniformGrid3d.h"

#include "../../Crystal/Shape/IParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

UniformGrid3d::UniformGrid3d(const double divideLength, const Vector3dd& min) :
	divideLength(divideLength)
{
	grid.resize(128);
	for (int i = 0; i < 128; ++i) {
		grid[i].resize(128);
		for (int j = 0; j < 128; ++j) {
			grid[i][j].resize(128);
		}
	}
}

void UniformGrid3d::add(IParticle* particle)
{
	const auto& index = toIndex(particle->getPosition());
	grid[index[0]][index[1]][index[2]].push_back(particle);
}

void UniformGrid3d::solveInteractions(IParticle* micro, const std::function<void(Shape::IParticle*, Shape::IParticle*)>& func)
{
	const auto position = micro->getPosition();
	const auto& index = toIndex(position);
	for (int i = index[0] - 1; i <= index[0] + 1; ++i) {
		for (int j = index[1] - 1; j <= index[1] + 1; ++j) {
			for (int k = index[2] - 1; k <= index[2] + 1; ++k) {
				const auto& points = grid[i][j][k];
				for (auto p : points) {
					const double d2 = Math::getDistanceSquared(p->getPosition(), position);
					if (d2 < divideLength * divideLength) {
						func(micro, p);
					}
				}
			}
		}
	}
}

std::array<int, 3> UniformGrid3d::toIndex(const Vector3df& pos)
{
	const int ix = static_cast<int>((pos[0]) / divideLength) + 1;
	const int iy = static_cast<int>((pos[1]) / divideLength) + 1;
	const int iz = static_cast<int>((pos[2]) / divideLength) + 1;
	return { ix, iy, iz };
}

