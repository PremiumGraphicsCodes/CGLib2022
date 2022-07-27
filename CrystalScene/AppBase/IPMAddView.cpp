#include "IPMAddView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"
#include "../Scene/PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

IPMAddView::IPMAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	nameView("Name", "PolygonMesh01"),
	materialView("Material", model),
	presenterView("Presenter")
//	attributeView("PSAttribute")
{
	add(&nameView);
	add(&materialView);
	add(&presenterView);
}

void IPMAddView::addPolygonMesh(const PolygonMeshBuilder& builder)
{
	auto world = getWorld();
	auto mesh = std::make_unique<PolygonMesh>();
	mesh->positions = builder.getPositions();
	mesh->normals = builder.getNormals();
	mesh->texCoords = builder.getTexCoords();
	mesh->vertices = builder.getVertices();
	mesh->faces = builder.getFaces();

	const auto materialName = materialView.getSelected();
	auto material = world->getScenes()->findSceneByName<MaterialScene*>(materialName);

	auto scene = new PolygonMeshScene(world->getNextSceneId(), nameView.getValue(), std::move(mesh));
	PolygonMeshScene::FaceGroup group(builder.getFaces(), material, nullptr);
	scene->addGroup(group);
	world->getScenes()->addScene(scene);

	//presenterView.setPresenter(scene, world);

	scene->getPresenter()->createView(getWorld()->getRenderer());
	
}