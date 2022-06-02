#include "MaterialScene.h"

#include "TextureScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

MaterialScene::MaterialScene(const int id, const std::string& name, std::unique_ptr<Material> material) :
	IScene(id, name),
	material(std::move(material))
{
	presenter = std::make_unique<MaterialPresenter>(this);
}