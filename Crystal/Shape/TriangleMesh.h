#pragma once

#include "../Shape/IShape.h"
#include "../Math/Triangle3d.h"

#include <vector>

namespace Crystal {
	namespace Shape {

class TriangleFace
{
public:
	TriangleFace()
	{}

	explicit TriangleFace(const Math::Triangle3d& triangle);

	TriangleFace(const Math::Triangle3d& triangle, const Math::Vector3dd& normal) :
		triangle(triangle),
		normal(normal)
	{}

	Math::Triangle3d triangle;
	Math::Vector3dd normal;
};

class TriangleMesh : public IShape
{
public:
	TriangleMesh();

	~TriangleMesh();

	void clear();

	Math::Vector3dd getCenter() const;

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	//Face* findFaceById(const int id);

	Math::Box3dd getBoundingBox() const override;

	std::vector<TriangleFace> getFaces() const { return faces; }

	void addFace(const TriangleFace& face);

public:
	std::vector<TriangleFace> faces;
};

	}
}