#include "LightAddView.h"

#include "Canvas.h"

#include "../Scene/World.h"
#include "../Command/Command.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

LightAddView::LightAddView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas),
	lightView("LAdd"),
	nameView("Name", "Light01")
{
	add(&lightView);
	add(&nameView);
}

void LightAddView::onOk()
{
	/*
	Crystal::Command::Command command(LightCreateLabels::CommandNameLabel);
	command.setArg(LightCreateLabels::PositionLabel, Vector3dd( lightView.position.getValue() ));
	command.setArg(LightCreateLabels::DiffuseLabel, ColorRGBAf( lightView.diffuse.getValue() ));
	command.setArg(LightCreateLabels::SpecularLabel, ColorRGBAf( lightView.specular.getValue() ));
	command.setArg(LightCreateLabels::AmbientLabel, ColorRGBAf(lightView.ambient.getValue()));
	command.setArg(LightCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());
	const auto newId = command.getResult(LightCreateLabels::NewIdLabel);
	*/
}
