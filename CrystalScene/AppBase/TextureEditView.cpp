#include "TextureEditView.h"

#include "../Scene/TextureScene.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

TextureEditView::TextureEditView(const std::string& name, World* model, Canvas* canvas) :
	IEditCancelView(name, model, canvas),
	idView("Id"),
	filePathView("FilePath")
{
	filePathView.addFilter("*.bmp");
	filePathView.addFilter("*.png");
	filePathView.addFilter("*.jpg");
	filePathView.addFilter("*.jpeg");

	add(&idView);
	add(&filePathView);
}

void TextureEditView::setValue(TextureScene* value)
{
	this->idView.setValue(value->getId());
//	this->filePathView.set
}

void TextureEditView::onEdit()
{
	/*
	Command::Command command(TextureSetLabels::CommandNameLabel);
	command.setArg(TextureSetLabels::IdLabel, idView.getValue());
	command.setArg(TextureSetLabels::FilePathLabel, filePathView.getFileName());
	command.execute(getWorld());
	*/
}
