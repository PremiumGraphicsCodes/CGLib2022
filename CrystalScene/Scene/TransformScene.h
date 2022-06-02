#pragma once

#include "IScene.h"

#include "Crystal/Math/Matrix3d.h"
#include "Crystal/Math/Matrix4d.h"

namespace Crystal {
	namespace Scene {

class TransformScene : public IScene
{
public:
	explicit TransformScene(const int id) :
		IScene(id)
	{}

	TransformScene(const int id, const std::string& name) :
		IScene(id, name)
	{}

	~TransformScene() {};

	Math::Matrix4dd getMatrix() const {
		return Math::Matrix4dd();
	}

	void setTranslate(const Math::Vector3dd& t) { this->translate = t; }

	Math::Vector3dd getTranslate() const { return translate; }

	SceneType getType() const override { return SceneTypeLabels::TransformScene; }

private:
	Math::Vector3dd translate;
	Math::Matrix3dd rotation;
};
	}
}