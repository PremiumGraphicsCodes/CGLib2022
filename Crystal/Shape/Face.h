#pragma once

#include <map>
#include <vector>
#include <array>
#include "../Math/Vector3d.h"
#include "../Math/Line3d.h"

namespace Crystal {
	namespace Math {
		class Triangle3d;
	}
	namespace Shape {

class Face
{
public:
	Face(int v1, int v2, int v3, int id) :
		vertexIds{ v1, v2, v3 },
		id(id),
		materialId(0)
	{}

	std::array<int, 3> getVertexIds() const { return vertexIds; }

	int getV1() const { return vertexIds[0]; }

	int getV2() const { return vertexIds[1]; }

	int getV3() const { return vertexIds[2]; }

	int getId() const { return id; }

	int materialId;

	Math::Triangle3d toTriangle(const std::vector<Math::Vector3dd>& positions) const;

	std::vector<Math::Line3dd> toLines(const std::vector<Math::Vector3dd>& positions) const;

private:
	int id;
	std::array<int, 3> vertexIds;
};

	}
}