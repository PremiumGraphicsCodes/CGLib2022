#include "TextureAddView.h"

#include "../Command/Command.h"

#include "../Scene/TextureScene.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

TextureAddView::TextureAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	filePathView("FilePath"),
	nameView("Name", std::string("TextureXXX"))
{
	filePathView.addFilter("*.bmp");
	filePathView.addFilter("*.png");
	filePathView.addFilter("*.jpg");
	filePathView.addFilter("*.jpeg");

	add(&filePathView);
	add(&nameView);
}

void TextureAddView::onOk()
{
	/*
	Command::Command command(TextureCreateLabels::CommandNameLabel);
	command.setArg(TextureCreateLabels::FilePathLabel, filePathView.getFileName());
	command.setArg(TextureCreateLabels::NameLabel, nameView.getValue());
	command.execute(getWorld());
	const auto newId = std::any_cast<int>( command.getResult(TextureCreateLabels::NewIdLabel) );
	
	auto scene = getWorld()->getScenes()->findSceneById<TextureScene*>(newId);
	auto controller = scene->getPresenter();
	controller->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	//getWorld()->getRenderer()->getScene()->screen.addChild(controller.getView());
	*/
}
