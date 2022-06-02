//from http://paulbourke.net/geometry/polygonise/

#include "../../Crystal/Math/Vector3d.h"
#include "MarchingCubesAlgo.h"
#include "MarchingCubesTable.h"
#include "CrystalScene/Scene/VolumeScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Space::MarchingCubesTable;

size_t MarchingCubesAlgo::build(const Volume<float>& volume, const double isoLevel)
{
	const auto unum = volume.getResolutions()[0];
	const auto vnum = volume.getResolutions()[1];
	const auto wnum = volume.getResolutions()[2];
	for (int i = 0; i < unum-1; ++i) {
		for (int j = 0; j < vnum-1; ++j) {
			for (int k = 0; k < wnum-1; ++k) {
				std::array<MCCell::Vertex, 8> vertices;

				vertices[0].position = volume.getCellPosition(i, j, k);
				vertices[0].value = volume.getValue(i,j,k);

				vertices[1].position = volume.getCellPosition(i+1, j, k);
				vertices[1].value = volume.getValue(i+1, j, k);

				vertices[2].position = volume.getCellPosition(i+1, j+1, k);
				vertices[2].value = volume.getValue(i+1, j+1, k);

				vertices[3].position = volume.getCellPosition(i, j + 1, k);
				vertices[3].value = volume.getValue(i, j+1, k);

				vertices[4].position = volume.getCellPosition(i, j, k+1);
				vertices[4].value = volume.getValue(i, j, k+1);

				vertices[5].position = volume.getCellPosition(i + 1, j, k+1);
				vertices[5].value = volume.getValue(i + 1, j, k+1);

				vertices[6].position = volume.getCellPosition(i + 1, j + 1, k+1);
				vertices[6].value = volume.getValue(i + 1, j + 1, k+1);

				vertices[7].position = volume.getCellPosition(i, j + 1, k+1);
				vertices[7].value = volume.getValue(i, j + 1, k+1);

				MCCell cell(vertices);
				march(cell, isoLevel);
			}
		}
	}
	return triangles.size();
}

void MarchingCubesAlgo::build(const SparseVolume<float>& volume, const float isoLevel)
{
	const auto nodes = volume.getNodes();

	for (const auto& n : nodes) {
		const auto ii = n->getIndex();
		std::array<MCCell::Vertex, 8> vertices;

		const auto i = ii[0];
		const auto j = ii[1];
		const auto k = ii[2];
		vertices[0].position = volume.getPositionAt(ii);
		vertices[0].value = volume.getValueAt(ii);

		const std::array<int, 3> i1 = { i + 1, j, k };
		vertices[1].position = volume.getPositionAt(i1);
		vertices[1].value = volume.getValueAt(i1);

		const std::array<int, 3> i2 = { i+ 1, j + 1,k };
		vertices[2].position = volume.getPositionAt(i2);
		vertices[2].value = volume.getValueAt(i2);

		const std::array<int, 3> i3 = { i, j + 1, k };
		vertices[3].position = volume.getPositionAt(i3);
		vertices[3].value = volume.getValueAt(i3);

		const std::array<int, 3> i4 = { i, j, k + 1 };
		vertices[4].position = volume.getPositionAt(i4);
		vertices[4].value = volume.getValueAt(i4);

		const std::array<int, 3> i5 = { i+1, j, k + 1 };
		vertices[5].position = volume.getPositionAt(i5);
		vertices[5].value = volume.getValueAt(i5);

		const std::array<int, 3> i6 = { i + 1, j+1, k + 1 };
		vertices[6].position = volume.getPositionAt(i6);
		vertices[6].value = volume.getValueAt(i6);

		const std::array<int, 3> i7 = { i, j + 1, k + 1 };
		vertices[7].position = volume.getPositionAt(i7);
		vertices[7].value = volume.getValueAt(i7);

		MCCell cell(vertices);
		march(cell, isoLevel);
	}
}


/*
   Given a grid cell and an isolevel, calculate the triangular
   facets required to represent the isosurface through the cell.
   Return the number of triangular facets, the array "triangles"
   will be loaded up with the vertices at most 5 triangular facets.
	0 will be returned if the grid cell is either totally above
   of totally below the isolevel.
*/
int MarchingCubesAlgo::march(const MCCell& cell, const double isolevel)
{
	Vector3dd vertlist[12];


	/*
	   Determine the index into the edge table which
	   tells us which vertices are inside of the surface
	*/
	int cubeindex = 0;
	if (cell.vertices[0].value < isolevel) cubeindex |= 1;
	if (cell.vertices[1].value < isolevel) cubeindex |= 2;
	if (cell.vertices[2].value < isolevel) cubeindex |= 4;
	if (cell.vertices[3].value < isolevel) cubeindex |= 8;
	if (cell.vertices[4].value < isolevel) cubeindex |= 16;
	if (cell.vertices[5].value < isolevel) cubeindex |= 32;
	if (cell.vertices[6].value < isolevel) cubeindex |= 64;
	if (cell.vertices[7].value < isolevel) cubeindex |= 128;

	/* Cube is entirely in/out of the surface */
	if (edgeTable[cubeindex] == 0)
		return(0);

	/* Find the vertices where the surface intersects the cube */
	if (edgeTable[cubeindex] & 1)
		vertlist[0] =
		getInterpolatedPosition(isolevel, cell.vertices[0], cell.vertices[1]);
	if (edgeTable[cubeindex] & 2)
		vertlist[1] =
		getInterpolatedPosition(isolevel, cell.vertices[1], cell.vertices[2]);
	if (edgeTable[cubeindex] & 4)
		vertlist[2] =
		getInterpolatedPosition(isolevel, cell.vertices[2], cell.vertices[3]);
	if (edgeTable[cubeindex] & 8)
		vertlist[3] =
		getInterpolatedPosition(isolevel, cell.vertices[3], cell.vertices[0]);
	if (edgeTable[cubeindex] & 16)
		vertlist[4] =
		getInterpolatedPosition(isolevel, cell.vertices[4], cell.vertices[5]);
	if (edgeTable[cubeindex] & 32)
		vertlist[5] =
		getInterpolatedPosition(isolevel, cell.vertices[5], cell.vertices[6]);
	if (edgeTable[cubeindex] & 64)
		vertlist[6] =
		getInterpolatedPosition(isolevel, cell.vertices[6], cell.vertices[7]);
	if (edgeTable[cubeindex] & 128)
		vertlist[7] =
		getInterpolatedPosition(isolevel, cell.vertices[7], cell.vertices[4]);
	if (edgeTable[cubeindex] & 256)
		vertlist[8] =
		getInterpolatedPosition(isolevel, cell.vertices[0], cell.vertices[4]);
	if (edgeTable[cubeindex] & 512)
		vertlist[9] =
		getInterpolatedPosition(isolevel, cell.vertices[1], cell.vertices[5]);
	if (edgeTable[cubeindex] & 1024)
		vertlist[10] =
		getInterpolatedPosition(isolevel, cell.vertices[2], cell.vertices[6]);
	if (edgeTable[cubeindex] & 2048)
		vertlist[11] =
		getInterpolatedPosition(isolevel, cell.vertices[3], cell.vertices[7]);

	/* Create the triangle */
	int ntriang = 0;
	for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
		const auto& v0 = vertlist[triTable[cubeindex][i]];
		const auto& v1 = vertlist[triTable[cubeindex][i + 1]];
		const auto& v2 = vertlist[triTable[cubeindex][i + 2]];

		Triangle3d triangle({ v0,v1,v2 });
		triangles.push_back(triangle);

		ntriang++;
	}

	return(ntriang);
}

Vector3dd MarchingCubesAlgo::getInterpolatedPosition(const double isolevel, const MCCell::Vertex& v1, const MCCell::Vertex& v2)
{
	if (::fabs(isolevel - v1.value) < 0.00001) {
		return v1.position;
	}
	if (::fabs(isolevel - v2.value) < 0.00001) {
		return v2.position;
	}
	if (::fabs(v1.value - v2.value) < 0.00001) {
		return v1.position;
	}
	const auto mu = (isolevel - v1.value) / (v2.value - v1.value);
	return v1.position + mu * (v2.position - v1.position);
}
