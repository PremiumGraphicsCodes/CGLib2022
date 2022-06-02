#pragma once

#include <array>

namespace Crystal {
	namespace Space {

class ZOrderCurve3d
{
public:
	static unsigned int encode(const std::array<unsigned int, 3>& index);

	static std::array<unsigned int,3> decode(const unsigned int x);

	static unsigned int getParent(unsigned int ltd, unsigned int rbd);

private:
	static unsigned int encode(unsigned int x);

	static unsigned int decode_(unsigned int x);
};

	}
}