#include "GLCube.h"

using namespace Crystal::Math;
using namespace Crystal::Renderer;

GLCube::GLCube() :
	GLCube(Vector3df(-1,-1,-1), Vector3df(1,1,1))
{

}

GLCube::GLCube(const Vector3df& min, const Vector3df& max) :
	min(min),
	max(max)
{
}

std::vector<Vector3df> GLCube::toGLArray() const
{
	return {};
}
