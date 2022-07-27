
#pragma once

#include "IShapeScene.h"
#include "MaterialScene.h"
#include "IPMPresenter.h"

#include "Crystal/Shape/PolygonMesh.h"
#include "Crystal/Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Scene {

class PolygonMeshScene : public IShapeScene
{
public:
	class FaceGroup
	{
	public:
		FaceGroup(const std::vector<Shape::Face>& faces, MaterialScene* material, TextureScene* texture) :
			faces(faces),
			material(material),
			texture(texture)
		{}

		std::vector<Shape::Face> faces;
		MaterialScene* material;
		TextureScene* texture;
	};

	PolygonMeshScene();

	PolygonMeshScene(const int id, const std::string& name, std::unique_ptr<Shape::PolygonMesh> shape);

	~PolygonMeshScene();

	Shape::PolygonMesh* getShape() const { return shape.get(); }

	void setShape(std::unique_ptr<Shape::PolygonMesh> shape) {
		this->shape = std::move(shape);
	}

	void translate(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	SceneType getType() const override { return SceneTypeLabels::PolygonMeshScene; }

	Math::Box3dd getBoundingBox() const override;

	IPresenter* getPresenter() override { return presenter.get(); }

	void setPresenter(std::unique_ptr<IPMPresenter> presenter) { this->presenter = std::move(presenter); }

	void addGroup(const FaceGroup& group) { this->groups.push_back(group); }

	std::vector<FaceGroup> getGroups() const { return groups; }

private:
	std::unique_ptr<Shape::PolygonMesh> shape;
	std::unique_ptr<IPMPresenter> presenter;
	std::vector<FaceGroup> groups;
};

	}
}