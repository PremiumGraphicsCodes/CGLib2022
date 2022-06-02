#pragma once

#include "TriangleMesh.h"
#include "../Util/UnCopyable.h"
#include <memory>

namespace Crystal {
	namespace Math {
		class Triangle3d;
		class Quad3d;
		template<typename T>
		class Box3d;
		template<typename T>
		class Sphere3d;
		class Cone3d;
		template<typename T>
		class ISurface3d;
		template<typename T>
		class IVolume3d;
	}
	namespace Shape {

class TriangleMeshBuilder : private UnCopyable
{
public:
	TriangleMeshBuilder();

	void add(const Math::Triangle3d& triangle);

	void add(const Math::Quad3d& quad);

	//void add(const Math::Box3dd& box);

	void add(const Math::ISurface3d<double>& sphere, const int unum, const int vnum);

	void add(const Math::IVolume3dd& volume, const int unum, const int vnum, const int wnum);

	/*
	void add(const Math::Sphere3d& sphere, const int unum, const int vnum);

	void add(const Math::Cone3d& cone, int unum);
	*/

	std::unique_ptr<TriangleMesh> build();

private:
	std::vector<TriangleFace> faces;

	void addFace(const Math::Vector3dd& v0, const Math::Vector3dd& v1, const Math::Vector3dd& v2);

	void addFace(const Math::Triangle3d& triangle);
};

	}
}