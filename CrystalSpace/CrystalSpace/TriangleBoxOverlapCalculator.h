#pragma once

namespace Crystal {
	namespace Space {

class TriangleBoxOverlapCalculator
{
public:
	static int triBoxOverlap(double boxcenter[3], double boxhalfsize[3], double triverts[3][3]);
};
	}
}