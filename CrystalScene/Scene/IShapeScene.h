#pragma once

#include "IScene.h"

#include "Crystal/Shape/IShape.h"

#include "Crystal/Math/Matrix3d.h"
#include "Crystal/Math/Matrix4d.h"

namespace Crystal {
	namespace Scene {

class IShapeScene : public IScene
{
public:
	explicit IShapeScene(const int id) :
		IScene(id)
	{}

	IShapeScene(const int id, const std::string& name) :
		IScene(id, name)
	{}

	virtual ~IShapeScene() {};

	virtual void translate(const Math::Vector3dd& v) = 0;

	virtual void transform(const Math::Matrix3dd& m) = 0;

	virtual void transform(const Math::Matrix4dd& m) = 0;

	//Shape::IShape* getShape() { return shape; }

private:
	//Shape::IShape* shape;
};
	}
}