#include "MeshToVolumeView.h"

#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "../CrystalVDB/VDBMeshToVolumeConverter.h"

#include "../CrystalVDB/VDBVolumeScene.h"

#include <iostream>

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

MeshToVolumeView::MeshToVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	vdbMeshSelectView("VDBMesh", model, canvas),
	divideLengthView("DivideLength", 1.0)
{

	add(&vdbMeshSelectView);
	add(&divideLengthView);
}

void MeshToVolumeView::onOk()
{
	const auto meshId = vdbMeshSelectView.getId();
	auto mesh = getWorld()->getScenes()->findSceneById<VDBMeshScene*>(meshId);

	auto volume = VDBMeshToVolumeConverter::toVolume(*mesh, divideLengthView.getValue());
	volume->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(volume);


	/*
	VDBVolume grid(1.0f);
	grid.fill(1, 6, -1.0f);

	VDBVolumeConverter vToMesh;
	VDBPolygonMesh* mesh = new VDBPolygonMesh();
	vToMesh.toMesh(grid, mesh);
	mesh->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(mesh);

	//EXPECT_FALSE(mesh->getVerticesf().empty());
	//EXPECT_EQ(216, mesh->getQuads().size());
	std::cout << "quads = " << mesh->getQuads().size() << std::endl;;
	*/
}