#include "MaterialEditView.h"

#include "../../Crystal/Graphics/Material.h"
#include "../Scene/MaterialScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialEditView::MaterialEditView(const std::string& name, World* world, Canvas* canvas) :
	IEditCancelView(name, world, canvas),
	idView("Id", 0),
	materialView("Material"),
	nameView("Name", "Material1")
{
	add(&idView);
	add(&materialView);
	add(&nameView);
}

void MaterialEditView::setValue(MaterialScene* value)
{
	this->idView.setValue(value->getId());
	this->nameView.setValue(value->getName());
	this->materialView.setValue(*(value->getMaterial()));
}

void MaterialEditView::onEdit()
{
	auto mat = getWorld()->getScenes()->findSceneById<MaterialScene*>(idView.getValue());
	auto material = mat->getMaterial();
	(*material) = this->materialView.getValue();
	//mat->setMaterial(materialView.getValue());
	//mat->setName(nameView.getValue());
}