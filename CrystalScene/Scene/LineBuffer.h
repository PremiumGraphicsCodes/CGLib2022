#pragma once

#include "Crystal/Math/Matrix4d.h"

#include "Crystal/Graphics/Buffer1d.h"
#include "Crystal/Graphics/Buffer3d.h"
#include "Crystal/Graphics/Buffer4d.h"

namespace Crystal {
	namespace Scene {

class LineBuffer
{
public:
	LineBuffer() :
		width(1.0f),
		matrix(Math::Identity<double>())
	{}

	explicit LineBuffer(const float width) :
		width(width),
		matrix(Math::Identity<double>())
	{};

	void addVertex(const Math::Vector3df& position, const Graphics::ColorRGBAf& color) {
		positions.add(position);
		colors.add(color);
	}

	void addIndex(const int index) {
		indices.add(index);
	}

	float getWidth() const { return width; }

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer4d<float> getColors() const { return colors; }

	Graphics::Buffer1d<unsigned int> getIndices() const { return indices; }

	void setMatrix(const Math::Matrix4dd& matrix) { this->matrix = matrix; }

	Math::Matrix4dd getMatrix() const { return matrix; }

private:
	Math::Matrix4dd matrix;
	float width;
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer4d<float> colors;
	Graphics::Buffer1d<unsigned int> indices;
};

	}
}