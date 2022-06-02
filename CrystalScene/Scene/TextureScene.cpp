#include "TextureScene.h"

#include "Crystal/Shader/TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

TextureScene::TextureScene(const int id, std::unique_ptr<Image> image, const std::string& name) :
	IScene(id, name),
	image(std::move(image))
{
	presenter = std::make_unique<TexturePresenter>(this);
}