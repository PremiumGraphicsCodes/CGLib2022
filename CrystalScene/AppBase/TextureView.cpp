#include "../../Crystal/Shader/glew.h"

#include "TextureView.h"

#include "CrystalUI/CrystalUI/imgui.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::UI;

TextureView::TextureView(const std::string& name) :
	TextureView(name, std::string(""))
{
}

TextureView::TextureView(const std::string& name, const std::string& filePath) :
	IView(name),
	filePathView(filePath),
	nameView("TextureName")
{
	add(&filePathView);
	add(&nameView);
}

void TextureView::setValue(const TextureObject& texture)
{
	//filePathView.set
}

