#include "TextureSetCommand.h"

#include "PublicLabel.h"

namespace TextureSetLabels
{
	PublicLabel CommandNameLabel = "TextureSet";

	PublicLabel IdLabel = "Id";
	PublicLabel FilePathLabel = "FilePath";

	PublicLabel IsOkLabel = "IsOk";
}

#include "../Scene/TextureScene.h"
#include "../../Crystal/IO/ImageFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::IO;
using namespace Crystal::Command;

std::string TextureSetCommand::getName()
{
	return TextureSetLabels::CommandNameLabel;
}

TextureSetCommand::Args::Args() :
	id(TextureSetLabels::IdLabel, -1),
	filePath(TextureSetLabels::FilePathLabel, std::string(""))
{
	add(&id);
	add(&filePath);
}

TextureSetCommand::Results::Results() :
	isOk(TextureSetLabels::IsOkLabel, false)
{
	add(&isOk);
}

bool TextureSetCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<TextureScene*>(args.id.getValue());
	if (scene == nullptr) {
		results.isOk.setValue(false);
		return false;
	}

	ImageFileReader reader;
	const auto isOk = reader.read(args.filePath.getValue());
	if (!isOk) {
		results.isOk.setValue(false);
		return false;
	}
	auto image = std::make_unique<Image>();
	*image = reader.getImage();
	scene->setImage(std::move(image));
	results.isOk.setValue(true);
	return true;
}
