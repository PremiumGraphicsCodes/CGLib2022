#pragma once

#include "IShape.h"

#include "../Math/Line3d.h"
#include "WireFrameEdge.h"
#include <vector>

namespace Crystal {
	namespace Shape {

class WireFrame : public IShape
{
public:
	WireFrame()
	{}

	WireFrame(const std::vector<Math::Vector3dd>& positions, const std::vector<WireFrameEdge>& edges) :
		positions(positions),
		edges(edges)
	{}

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	void clear() {
		positions.clear();
		edges.clear();
	}

	Math::Box3dd getBoundingBox() const override;

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

	std::vector<WireFrameEdge> getEdges() const { return edges; }

private:
	std::vector<Math::Vector3dd> positions;
	std::vector<WireFrameEdge> edges;
};

	}
}