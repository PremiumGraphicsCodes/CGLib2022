#include "SPHVolumeConverterView.h"

#include "../CrystalPhysics/SurfaceConstruction/SPHVolumeConverter.h"

#include "Crystal/Shape/Particle.h"
#include "Crystal/Shape/WireFrameBuilder.h"

#include "CrystalScene/Scene/WireFrameScene.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"

#include "CrystalSpace/CrystalSpace/SparseVolumeScene.h"

#include "Crystal/Math/Sphere3d.h"
#include "Crystal/Math/Ellipsoid3d.h"

#include "CrystalSpace/CrystalSpace/MarchingCubesAlgo.h"
//#include "Crystal/Shape/PolygonMeshBuilder.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::Physics;

namespace {
	constexpr auto tolerance = 1.0e-12;

	void build(const Sphere3dd& sphere, const int unum, const int vnum, const Matrix3dd& m, WireFrameBuilder& wfBuilder)
	{
		const auto du = 1.0 / static_cast<double>(unum);
		const auto dv = 1.0 / static_cast<double>(vnum);

		std::vector<std::vector<int>> grid;
		for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
			std::vector<int> g;
			for (auto v = 0.0; v < 1.0 + tolerance; v += dv) {
				auto p = sphere.getPosition(u, v);
				p -= sphere.getCenter();
				p = m * p * glm::determinant(m);
				p += sphere.getCenter();
				g.push_back(wfBuilder.createPosition(p));
			}
			grid.push_back(g);
		}
		for (int i = 0; i < grid.size() - 1; ++i) {
			for (int j = 0; j < grid[i].size() - 1; ++j) {
				const auto v1 = grid[i][j];
				const auto v2 = grid[i + 1][j];
				const auto v3 = grid[i + 1][j + 1];
				const auto v4 = grid[i][j + 1];
				wfBuilder.addEdge(WireFrameEdge(v1, v2));
				wfBuilder.addEdge(WireFrameEdge(v2, v3));
				wfBuilder.addEdge(WireFrameEdge(v3, v4));
				wfBuilder.addEdge(WireFrameEdge(v4, v1));
			}
		}
	}
}

SPHVolumeConverterView::SPHVolumeConverterView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleRadiusView("ParticleRadius", 1.0f),
	cellLengthView("CellLength", 1.0),
	thresholdView("Threshold", 1.0f),
	colorMapView("ColorMap")
{
	add(&particleRadiusView);
	add(&cellLengthView);
	add(&thresholdView);
	add(&colorMapView);
}

void SPHVolumeConverterView::onOk()
{
	std::vector<Vector3dd> positions;

	/*
	Sphere3d sphere(Vector3dd(0,0,0), 10);
	for (auto u = 0.0; u < 1.0; u += 0.1) {
		for (auto v = 0.0; v < 1.0; v +=0.1) {
			for (auto w = 0.0; w < 1.0; w += 0.1) {
				positions.push_back( sphere.getPosition(u, v, w) );
			}
		}
	}
	*/
	//sphere.getPosition()

	const Sphere3d sphere(Vector3dd(50, 50, 50), 10.0);
	const Box3d box = sphere.getBoundingBox();
	const auto center = sphere.getCenter();
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				const auto u = i / 10.0;
				const auto v = j / 10.0;
				const auto w = k / 10.0;
				const auto p = box.getPosition(u,v,w);
				if (sphere.isInside(p)) {
					positions.push_back(p);
				}
			}
		}
	}
	//positions.emplace_back(0, 0, 0);

	//Crystal::IO::PCDBinaryFileReader reader;
	//reader.read("C://Dev//cgstudio4//Blender//CrystalPython//tmp_txt/macro1.pcd");
	//positions = reader.getPCD().data.positions;

	auto world = getWorld();

	SPHVolumeConverter builder;
	auto sp = builder.buildIsotoropic(positions, particleRadiusView.getValue(), cellLengthView.getValue());
	//auto sp = builder.buildAnisotoropic(positions, particleRadiusView.getValue(), cellLengthView.getValue());

	//auto volumes = builder.getVolumes();
	const auto nodes = sp->getNodes();
	float maxValue = std::numeric_limits<float>::lowest();
	float minValue = std::numeric_limits<float>::max();
	for (auto n : nodes) {
		maxValue = std::max(maxValue, n->getValue());
		minValue = std::min(minValue, n->getValue());
	}
	std::cout << minValue << std::endl;
	std::cout << maxValue << std::endl;

	SparseVolumeScene* svScene = new SparseVolumeScene(getWorld()->getNextSceneId(), "Vol", std::move(sp));
	auto presenter = svScene->getPresenter();

	auto colorMap = this->colorMapView.getValue();
	colorMap.setMinMax(minValue,maxValue);
	static_cast<SparseVolumePresenter*>(presenter)->setColorMap(colorMap);
	presenter->createView(world->getRenderer());

	getWorld()->getScenes()->addScene(svScene);
}