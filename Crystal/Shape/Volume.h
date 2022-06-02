#pragma once

#include "IShape.h"

#include "Particle.h"

#include "../Math/Box3d.h"

#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

#include "../Util/Array3d.h"

#include <array>
#include <vector>

namespace Crystal {
	namespace Shape {

template<typename T>
class Volume : public IShape
{
public:
	Volume();

	Volume(const Math::Box3dd& box, const std::array<size_t, 3>& resolutions);

	Volume(const Math::Box3dd& box, const Util::Array3d<T>& nodes);

	~Volume() {
		//clear();
	}

	void move(const Math::Vector3dd& v) override {
		box.translate(v);
	}

	void transform(const Math::Matrix3dd& m) override {

	}

	void transform(const Math::Matrix4dd& m) override {

	}

	Math::Box3dd getBoundingBox() const override { return box; }

	std::array<size_t,3> getResolutions() const { return nodes.getResolutions(); }

	Math::Vector3dd getCellPosition(const size_t i, const size_t j, const size_t k) const;

	std::array<size_t, 3> getIndexFromPosition(const Math::Vector3dd& position);

	Math::Vector3dd getCellLength() const;

	T getValue(const size_t i, const size_t j, const size_t k) const { return nodes.get(i,j,k); }

	void setValue(const size_t i, const size_t j, const size_t k, const T value) { nodes.set(i,j,k, value); }

	Util::Array3d<T> getNodes() const { return nodes; }

	void fill(const T value) { this->nodes.fill(value); }

private:
	Math::Box3dd box;
	Util::Array3d<T> nodes;
};

	}
}
