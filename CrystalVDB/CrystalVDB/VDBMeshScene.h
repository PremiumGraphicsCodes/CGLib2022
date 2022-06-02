#pragma once

#include "../../Crystal/Math/Vector3d.h"

#include "../../CrystalScene/Scene/IShapeScene.h"

#include "VDBMeshPresenter.h"

#include <memory>
#include <array>
#include <vector>

namespace Crystal {
	namespace VDB {
		class VDBMeshImpl;

class VDBMeshScene : public Scene::IShapeScene
{
public:
	struct TriangleFace
	{
		std::array<unsigned int, 3> indices;
		Math::Vector3df normal;
	};

	struct QuadFace
	{
		std::array<unsigned int, 4> indices;
		Math::Vector3df normal;
	};

	struct Face
	{
		std::vector<unsigned int> indices;
		Math::Vector3df normal;
	};

	VDBMeshScene();

	VDBMeshScene(const int id, const std::string& name);

	~VDBMeshScene();

	void addVertex(const Math::Vector3df& position);

	Math::Vector3df getVertex(const int index);

	std::vector<Math::Vector3df> getVerticesf() const;

	std::vector<Math::Vector3dd> getVerticesd() const;

	void addTriangle(const std::array<unsigned int, 3>& indices);

	std::vector<TriangleFace> getTriangleFaces() const;

	void addQuad(const std::array<unsigned int, 4>& indices);

	std::vector<QuadFace> getQuadFaces() const;

	std::vector<Face> getAllFaces() const;

	void translate(const Math::Vector3dd& v) override {};

	void transform(const Math::Matrix3dd& m) override {};

	void transform(const Math::Matrix4dd& m) override {};

	Scene::IPresenter* getPresenter() { return presenter.get(); }

	static constexpr auto Type = "VDBPolygonMesh";

	Scene::SceneType getType() const { return Type; }

	Math::Box3dd getBoundingBox() const override;

	void updateNormals();

	VDBMeshImpl* getImpl() const { return impl.get(); }

	void scale(const double scale);

private:
	std::unique_ptr<VDBMeshImpl> impl;
	std::unique_ptr<VDBMeshPresenter> presenter;
};

	}
}