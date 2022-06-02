#pragma once

#include "IScene.h"
#include "Crystal/Graphics/Image.h"
#include "TexturePresenter.h"

namespace Crystal {
	namespace Scene {

class TextureScene : public IScene
{
public:
	TextureScene(const int id, std::unique_ptr<Graphics::Image> image, const std::string& name);

	~TextureScene() {};

	SceneType getType() const override { return SceneTypeLabels::TextureScene; }

	void setImage(std::unique_ptr<Graphics::Image> image) { this->image = std::move(image); }

	Graphics::Image* getImage() { return image.get(); }

	IPresenter* getPresenter() override { return presenter.get(); }

private:
	std::unique_ptr<Graphics::Image> image;
	std::unique_ptr<TexturePresenter> presenter;
};

	}
}