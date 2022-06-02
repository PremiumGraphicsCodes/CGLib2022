#pragma once

#include <array>
#include "../../Crystal/Math/Vector3d.h"

namespace Crystal {
	namespace Space {

struct MCCell
{
	struct Vertex
	{
		Vertex()
		{}

		Vertex(const Math::Vector3dd& position, double value) :
			position(position),
			value(value)
		{}

		Math::Vector3dd position;
		double value;
	};

	MCCell()
	{}

	explicit MCCell(const std::array<Vertex, 8>& vertices) :
		vertices(vertices)
	{
	}

	std::array<Vertex, 8> vertices;
};

	}
}