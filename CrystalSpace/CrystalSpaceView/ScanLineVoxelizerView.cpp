#include "ScanLineVoxelizerView.h"

#include "../CrystalSpace/ScanLineVoxelizer.h"

#include "CrystalScene/Scene/VoxelScene.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"

//#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "Crystal/Shape/TriangleMeshBuilder.h"
#include "Crystal/Math/Sphere3d.h"

#include "Crystal/IO/TXTFileWriter.h"


using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;

ScanLineVoxelizerView::ScanLineVoxelizerView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	divideLengthView("DivideLength", 1.0)
{
	add(&divideLengthView);
}

void ScanLineVoxelizerView::onOk()
{
	TriangleMeshBuilder builder;
	const Box3d box(Vector3dd(2, 2, 2), Vector3dd(8, 8, 8));
	builder.add(box, 2, 2, 2);
	//const Sphere3dd sphere(Vector3dd(5, 5, 5), 5);
	//builder.add(sphere, 32, 32);
	auto mesh = builder.build();
	std::vector<Triangle3d> triangles;
	const auto fs = mesh->getFaces();
	for (auto f : fs) {
		triangles.push_back(f.triangle);
	}

	const Box3d space(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));

	ScanLineVoxelizer voxelizer;
	voxelizer.voxelize(triangles, space, 1.0);
	auto voxel = voxelizer.getVoxel();

	const auto& intersections = voxelizer.getIntersections();
	auto ps = std::make_unique<ParticleSystem<ParticleAttribute>>();

	ParticleAttribute attr;
	attr.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
	attr.size = 100.0f;
	for (const auto& p : intersections) {
		ps->add(p, attr);
	}

	auto scene = new ParticleSystemScene(getWorld()->getNextSceneId(), "", std::move(ps));
	getWorld()->getScenes()->addScene(scene);
	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer());

	{
		TXTFileWriter writer;
		for (int i = 0; i < voxel->getResolutions()[0]; ++i) {
			for (int j = 0; j < voxel->getResolutions()[1]; ++j) {
				for (int k = 0; k < voxel->getResolutions()[2]; ++k) {
					if (voxel->getValue(i, j, k)) {
						auto p = voxel->getCellPosition(i, j, k);
						writer.add(p);
					}
				}
			}
		}
		writer.write("voxelized.txt");
	}

	{
		auto scene = new VoxelScene(getWorld()->getNextSceneId(), "Voxelized", std::move(voxel));
		auto presenter = scene->getPresenter();
		presenter->createView(getWorld()->getRenderer());
	}
}