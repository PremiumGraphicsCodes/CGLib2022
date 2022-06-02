#include "MaterialAddView.h"

#include "../../Crystal/Graphics/Material.h"
#include "../Scene/World.h"
#include "Canvas.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;

MaterialAddView::MaterialAddView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas),
	materialView("Material"),
	nameView("Name", "Material1")
{
	add(&materialView);
	add(&nameView);
}

void MaterialAddView::onOk()
{
	/*
	Crystal::Command::Command command(MaterialCreateLabels::CommandNameLabel);
	command.setArg(MaterialCreateLabels::AmbientLabel, materialView.ambientView.getValue());
	command.setArg(MaterialCreateLabels::DiffuseLabel, materialView.diffuseView.getValue());
	command.setArg(MaterialCreateLabels::SpecularLabel, materialView.specularView.getValue());
	command.setArg(MaterialCreateLabels::ShininessLabel, materialView.shininessView.getValue());
	//command.setArg(MaterialCreateLabels::AmbientTextureNameLabel, m.ambientTextureName);
	//command.setArg(MaterialCreateLabels::DiffuseTextureNameLabel, m.diffuseTextureName);
	//command.setArg(MaterialCreateLabels::SpecularTextureNameLabel, m.specularTextureName);
	command.setArg(MaterialCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());
	const auto newId = command.getResult(MaterialCreateLabels::NewIdLabel);
	*/
}
