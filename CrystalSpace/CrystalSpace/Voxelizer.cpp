#include "Voxelizer.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "SpaceHash3d.h"
#include "Overlap.h"

using namespace Crystal::Util;
using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	const auto e = 1.0e-12;
}

void Voxelizer::voxelize(const PolygonMesh& polygon, const double res)
{
	const auto bb = polygon.getBoundingBox();
	const auto xres = static_cast<size_t>( bb.getLength().x / res) + 1;
	const auto yres = static_cast<size_t>( bb.getLength().y / res) + 1;
	const auto zres = static_cast<size_t>( bb.getLength().z / res) + 1;
	std::array<size_t, 3> ress = { xres, yres, zres };

	const auto faces = polygon.getFaces();
	const auto size = static_cast<int>(faces.size() * 3);
	SpaceHash3d table(res, size);

	const auto voxelSize = Vector3dd(res);
	
	std::vector<IParticle*> particles;
	for (const auto& f : faces) {
		const auto triangle = f.toTriangle(polygon.getPositions());
		if (triangle.getArea() < e) {
			continue;
		}
		const auto smallBB = triangle.getBoundingBox();

		for (auto x = smallBB.getMinX(); x < smallBB.getMaxX() + e; x += voxelSize.x) {
			for (auto y = smallBB.getMinY(); y < smallBB.getMaxY() + e; y += voxelSize.y) {
				for (auto z = smallBB.getMinZ(); z < smallBB.getMaxZ() + e; z += voxelSize.z) {
					const Vector3dd p(x, y, z);
					const auto v1 = p - voxelSize * 0.5;// - 1.0e-3;
					const auto v2 = p + voxelSize * 0.5;// + 1.0e-3;
					Box3dd smallBox(v1, v2);
					if (Overlap::overlap(smallBox, triangle)) {
						auto particle = new Particle<bool>(p, false);
						particles.push_back(particle);
						table.add(particle);
					}
				}
			}
		}
	}

	this->voxel = std::make_unique<Voxel>(bb, ress);
	voxel->fill(false);

	{
		for (int i = 0; i < xres; ++i) {
			const auto x = bb.getMinX() + i * voxelSize.x;
			for (int j = 0; j < yres; ++j) {
				const auto y = bb.getMinY() + j * voxelSize.y;
				for (int k = 0; k < zres; ++k) {
					const auto z = bb.getMinZ() + k * voxelSize.z;
					const Vector3dd p(x, y, z);
					if (!table.isEmpty(p)) {
						voxel->setValue(i, j, k, true);
					}
				}
			}
		}
	}
	for (auto p : particles) {
		delete p;
	}
}

// reference https://github.com/sylefeb/VoxSurf/blob/master/main.cpp

/*
void Voxelizer::fill()
{
	const auto resolutions = voxel->getResolutions();

	const auto voxelX = scanX();
	const auto voxelY = scanY();
	const auto voxelZ = scanZ();

	for (int i = 0; i < resolutions[0]; ++i) {
		for (int j = 0; j < resolutions[1]; ++j) {
			for (int k = 0; k < resolutions[2]; ++k) {
				const auto xIsInside = (voxelX.get(i, j, k) % 2) == 1;
				const auto yIsInside = (voxelY.get(i, j, k) % 2) == 1;
				const auto zIsInside = (voxelZ.get(i, j, k) % 2) == 1;
				if (xIsInside && yIsInside && zIsInside) {
					voxel->setValue(i, j, k, true);
				}
			}
		}
	}
}
*/

// along x.
Array3d<unsigned int> Voxelizer::scanX()
{
	Array3d<unsigned int> array3d(voxel->getResolutions(), 0);
	const auto& resolutions = array3d.getResolutions();

	for (int k = 0; k < resolutions[2]; ++k) {
		for (int j = 0; j < resolutions[1]; ++j) {
			unsigned int count = 0;
			for (int i = 0; i < resolutions[0]; ++i) {
				if (voxel->getValue(i, j, k)) {
					count++;
				}
				array3d.set(i, j, k, count);
			}
		}
	}
	return array3d;
}

// along y
Array3d<unsigned int> Voxelizer::scanY()
{
	Array3d<unsigned int> array3d(voxel->getResolutions(), 0);
	const auto& resolutions = array3d.getResolutions();

	for (int k = 0; k < resolutions[2]; ++k) {
		for (int i = 0; i < resolutions[0]; ++i) {
			unsigned int count = 0;
			for (int j = 0; j < resolutions[1]; ++j) {
				if (voxel->getValue(i, j, k)) {
					count++;
				}
				array3d.set(i, j, k, count);
			}
		}
	}
	return array3d;
}

// along z
Array3d<unsigned int> Voxelizer::scanZ()
{
	Array3d<unsigned int> array3d(voxel->getResolutions(), 0);
	const auto& resolutions = array3d.getResolutions();

	for (int j = 0; j < resolutions[1]; ++j) {
		for (int i = 0; i < resolutions[0]; ++i) {
			unsigned int count = 0;
			for (int k = 0; k < resolutions[2]; ++k) {
				if (voxel->getValue(i, j, k)) {
					count++;
				}
				array3d.set(i, j, k, count);
			}
		}
	}
	return array3d;
}