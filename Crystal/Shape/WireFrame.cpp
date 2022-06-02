#include "WireFrame.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

void WireFrame::move(const Vector3dd& v)
{
	for (auto& l : positions) {
		l += v;
	}
}

void WireFrame::transform(const Matrix3dd& m)
{
	for (auto& l : positions) {
		l = m * l;
	}
}

void WireFrame::transform(const Matrix4dd& m)
{
	for (auto& l : positions) {
		l = m * glm::vec4(l, 1.0);
	}
}

Box3dd WireFrame::getBoundingBox() const
{
	if (positions.empty()) {
		return Box3dd();
	}
	Box3d bb(positions.front());
	for (const auto& v : positions) {
		bb.add(v);
	}
	bb.add(bb);
	return bb;
}