#pragma once

#include "../Math/IVolume3d.h"

#include "IShape.h"
#include <memory>

namespace Crystal {
	namespace Shape {

class Solid : public IShape
{
public:
	explicit Solid(std::unique_ptr<Math::IVolume3dd> shape);

	~Solid() {};

	void move(const Math::Vector3dd& v) {}

	void transform(const Math::Matrix3dd& m) { matrix *= Math::Matrix4dd(m); }

	void transform(const Math::Matrix4dd& m) { matrix *= m; }

	Math::Box3dd getBoundingBox() const override;

private:
	std::unique_ptr<Math::IVolume3dd> shape;
	Math::Matrix4dd matrix;
};

	}
}