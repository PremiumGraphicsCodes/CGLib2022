#include "MeshBoundaryScene.h"

#include "MeshBoundaryScenePresenter.h"
#include "Crystal/Math/Triangle3d.h"
//#include "../../CrystalSpace/CrystalSpace/MeshToParticleAlgo.h"
#include "Crystal/Shape/Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
//using namespace Crystal::Space;
using namespace Crystal::Physics;

MeshBoundaryScene::MeshBoundaryScene(const int id, const std::string& name) :
	IScene(id, name),
	mesh(nullptr)
{
	this->controller = std::make_unique<MeshBoundaryScenePresenter>(this);
}

MeshBoundaryScene::~MeshBoundaryScene()
{
}

void MeshBoundaryScene::build(Shape::PolygonMesh* mesh, const double divideLength)
{
	/*
	this->mesh = mesh;
	this->divideLength = divideLength;
	const auto& positions = mesh->getPositions();
	const auto& faces = mesh->getFaces();

	MeshToParticleAlgo particleConverter;
	for (const auto& f : faces) {
		particleConverter.subdivide(f.toTriangle(positions), divideLength);
	}
	const auto& divPositions = particleConverter.getPositions();
	const auto& normals = particleConverter.getNormals();
	assert(divPositions.size() == normals.size());

	for (int i = 0; i < divPositions.size(); ++i) {
		auto pn = new Particle<BoundaryAttr>(divPositions[i], BoundaryAttr(normals[i]));
		positionWithNormal.push_back(pn);
	}
	*/
}

IPresenter* MeshBoundaryScene::getPresenter()
{
	return controller.get();
}

Box3dd MeshBoundaryScene::getBoundingBox() const
{
	return mesh->getBoundingBox();
}