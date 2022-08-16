#include "GLCube.h"

#include "Crystal/Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Renderer;

/*
std::vector<float> getCubePositions()
{
    Crystal::Shape::TriangleMeshBuilder builder;
    Box3dd box(Vector3dd(-1, -1, -1), Vector3dd(1, 1, 1));
    builder.add(box, 2, 2, 2);
    const auto tm = builder.build();
    const auto fs = tm->getFaces();
    std::vector<float> positions;
    for (auto t : fs) {
        const auto v0 = t.triangle.getV0();
        const auto v1 = t.triangle.getV1();
        const auto v2 = t.triangle.getV2();
        positions.push_back(v0.x);
        positions.push_back(v0.y);
        positions.push_back(v0.z);
        positions.push_back(v1.x);
        positions.push_back(v1.y);
        positions.push_back(v1.z);
        positions.push_back(v2.x);
        positions.push_back(v2.y);
        positions.push_back(v2.z);
    }
    return positions;
}
*/

GLCube::GLCube() :
	GLCube(Vector3df(-1,-1,-1), Vector3df(1,1,1))
{

}

GLCube::GLCube(const Vector3df& min, const Vector3df& max) :
	min(min),
	max(max)
{
}

std::vector<float> GLCube::toGLArray() const
{
	Box3dd volume(min, max);
	const auto v0 = volume.getPosition(0, 0, 0);
	const auto v1 = volume.getPosition(1, 0, 0);
	const auto v2 = volume.getPosition(1, 1, 0);
	const auto v3 = volume.getPosition(0, 1, 0);

	const auto v4 = volume.getPosition(0, 0, 1);
	const auto v5 = volume.getPosition(1, 0, 1);
	const auto v6 = volume.getPosition(1, 1, 1);
	const auto v7 = volume.getPosition(0, 1, 1);

	std::vector<Vector3df> vertices = {
		v0, v1, v2,
		v2, v3, v0,
		v1, v5, v6,
		v6, v2, v1,
		v6, v5, v4,
		v4, v7, v6,
		v4, v0, v3,
		v7, v4, v3,
		v6, v3, v2,
		v7, v3, v6,
		v0, v5, v1,
		v0, v4, v5
	};

	std::vector<float> data;
	for (const auto& v : vertices) {
		data.push_back(v.x);
		data.push_back(v.y);
		data.push_back(v.z);
	}
	//addFace(v0, v1, v2); // front
	//addFace(v2, v3, v0);

	//addFace(v1, v5, v6); // right
	//addFace(v6, v2, v1);

	//addFace(v6, v5, v4); // left
	//addFace(v4, v7, v6);

	//addFace(v4, v0, v3); // back
	//addFace(v7, v4, v3);

	//addFace(v6, v3, v2); // top;
	//addFace(v7, v3, v6);

	//addFace(v0, v5, v1); // bottom
	//addFace(v0, v4, v5);

	return data;
}
