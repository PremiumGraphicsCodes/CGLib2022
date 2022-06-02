#pragma once

#include "Crystal/Graphics/Buffer1d.h"
#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Graphics/Buffer4d.h"

namespace Crystal {
	namespace Scene {

class TriangleBuffer
{
public:
	TriangleBuffer()
	{}

	void addVertex(const Math::Vector3df& position, const Graphics::ColorRGBAf& color) {
		positions.add(position);
		colors.add(color);
	}

	void addIndex(const int index) {
		indices.add(index);
	}

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer4d<float> getColors() const { return colors; }

	Graphics::Buffer1d<unsigned int> getIndices() const { return indices; }

private:
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer4d<float> colors;
	Graphics::Buffer1d<unsigned int> indices;
};

	}
}