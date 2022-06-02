#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Vector3d.h"
#include <vector>
#include <array>
#include <list>
#include <functional>

namespace Crystal {
	namespace Shape {
		class IParticle;
	}
	namespace Space {

class UniformGrid3d : private UnCopyable
{
public:
	UniformGrid3d(const double divideLength, const Math::Vector3dd& min);

	void add(Shape::IParticle* particle);

	void solveInteractions(Shape::IParticle* micro, const std::function<void(Shape::IParticle*, Shape::IParticle*)>& func);

private:
	std::vector<std::vector<std::vector<std::list<Shape::IParticle*>>>> grid;

	std::array<int, 3> toIndex(const Math::Vector3df& pos);

	const double divideLength;
};

	}
}