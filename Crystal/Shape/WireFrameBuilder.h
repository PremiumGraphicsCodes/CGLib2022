#pragma once

#include <vector>
#include <memory>

#include "../Math/Vector3d.h"

#include "WireFrameEdge.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class ICurve3d;
		template<typename T>
		class ISurface3d;
		template<typename T>
		class IVolume3d;
	}
	namespace Shape {
		class WireFrame;

class WireFrameBuilder
{
public:
	void add(const Math::ICurve3d<double>& curve, int unum);

	void add(const Math::ISurface3d<double>& circle, const int unum, const int vnum);

	void add(const Math::IVolume3d<double>& box);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

	std::vector<WireFrameEdge> getEdges() const { return edges; }

	int createPosition(const Math::Vector3dd& v);

	void addEdge(const WireFrameEdge& e) { this->edges.push_back(e); }

	std::unique_ptr<WireFrame> createWireFrame();

	void clear();

private:
	void add(const std::vector<std::vector<int>>& grid);

private:
	std::vector<Math::Vector3dd> positions;
	std::vector<WireFrameEdge> edges;
};

	}
}