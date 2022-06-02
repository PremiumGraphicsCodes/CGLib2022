#include "Line2d.h"

using namespace Crystal::Math;

Line2dd::Line2dd() :
	origin(0, 0),
	dir(1, 0)
{
}

Line2dd::Line2dd(const Vector2dd& origin, const Vector2dd& dir) :
	origin(origin),
	dir(dir)
{
}
