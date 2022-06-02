#include "VDBMeshScene.h"

#include "VDBMeshImpl.h"
#include "Converter.h"

#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBMeshScene::VDBMeshScene() :
	VDBMeshScene(-1, "")
{
	impl = std::make_unique<VDBMeshImpl>();
}

VDBMeshScene::VDBMeshScene(const int id, const std::string& name) :
	IShapeScene(id, name)
{
	impl = std::make_unique<VDBMeshImpl>();
	presenter = std::make_unique<VDBMeshPresenter>(this);
}

VDBMeshScene::~VDBMeshScene()
{

}

void VDBMeshScene::addVertex(const Vector3df& position)
{
	impl->points.push_back(Converter::toVDB(position));
}

Vector3df VDBMeshScene::getVertex(const int index)
{
	return Converter::fromVDB( impl->points[index] );
}

std::vector<Vector3df> VDBMeshScene::getVerticesf() const
{
	return Converter::fromVDBf<Vector3df>(impl->points);
}

std::vector<Vector3dd> VDBMeshScene::getVerticesd() const
{
	return Converter::fromVDBf<Vector3dd>(impl->points);
}

void VDBMeshScene::addTriangle(const std::array<unsigned int, 3>& indices)
{
	VDBMeshImpl::TriangleFace triangle;
	triangle.indices = Converter::toVDB( indices );
	//triangle.normal = Converter::toVDB(normal);
	impl->triangles.push_back(triangle);
}

std::vector<VDBMeshScene::TriangleFace> VDBMeshScene::getTriangleFaces() const
{
	std::vector<VDBMeshScene::TriangleFace> faces;
	for (const auto& t : impl->triangles) {
		VDBMeshScene::TriangleFace face;
		face.indices = Converter::fromVDB(t.indices);
		face.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(face);
	}
	return faces;
}

void VDBMeshScene::addQuad(const std::array<unsigned int, 4>& indices)
{
	VDBMeshImpl::QuadFace quad;
	quad.indices = Converter::toVDB(indices);
	//quad.normal = Converter::toVDB(normal);
	impl->quads.push_back(quad);
}

std::vector<VDBMeshScene::QuadFace> VDBMeshScene::getQuadFaces() const
{
	std::vector<VDBMeshScene::QuadFace> faces;
	for (const auto& q : impl->quads) {
		VDBMeshScene::QuadFace face;
		face.indices = Converter::fromVDB(q.indices);
		face.normal = Converter::fromVDB(q.normal);
		faces.emplace_back(face);
	}
	return faces;
}

std::vector<VDBMeshScene::Face> VDBMeshScene::getAllFaces() const
{
	std::vector<VDBMeshScene::Face> faces;
	for (const auto& t : impl->triangles) {
		VDBMeshScene::Face f;
		f.indices = { t.indices[0], t.indices[1], t.indices[2] };
		f.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(f);
	}
	for (const auto& t : impl->quads) {
		VDBMeshScene::Face f;
		f.indices = { t.indices[0], t.indices[1], t.indices[2], t.indices[3] };
		f.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(f);
	}
	return faces;
}

Box3dd VDBMeshScene::getBoundingBox() const
{
	if (impl->points.empty()) {
		return Box3dd::createDegeneratedBox();
	}
	auto vertices = this->getVerticesd();

	Math::Box3d box(vertices[0]);
	for (auto v : vertices) {
		box.add(v);
	}
	return box;
}

void VDBMeshScene::updateNormals()
{
	impl->updateNormals();
}

void VDBMeshScene::scale(const double scale)
{
	for (auto& p : impl->points) {
		p *= scale;
	}
}
