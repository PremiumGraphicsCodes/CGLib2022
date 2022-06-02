#pragma once

#include "IShape.h"

namespace Crystal {
	namespace Shape {

class CSG : public IShape
{
public:
	~CSG() {};

	void move(const Math::Vector3dd& v) {}

	void transform(const Math::Matrix3dd& m) {}

	void transform(const Math::Matrix4dd& m) {}

	Math::Box3dd getBoundingBox() { return Math::Box3dd(); }

private:

};

	}
}