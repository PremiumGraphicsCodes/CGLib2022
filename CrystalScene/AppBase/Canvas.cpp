#include "Canvas.h"
#include "CameraUICtrl.h"
#include "../../Crystal/Math/Box3d.h"
#include "../Scene/World.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

Canvas::Canvas() :
	width(0),
	height(0)
{
}

void Canvas::onLeftButtonDown(const Vector2df& position)
{
	ctrl->onLeftButtonDown(position);
}

void Canvas::onLeftButtonUp(const Vector2df& position)
{
	ctrl->onLeftButtonUp(position);
}

void Canvas::onRightButtonDown(const Vector2df& position)
{
	ctrl->onRightButtonDown(position);
}

void Canvas::onRightButtonUp(const Vector2df& position)
{
	ctrl->onRightButtonUp(position);
}

void Canvas::onMiddleButtonDown(const Vector2df& position)
{
	ctrl->onMiddleButtonDown(position);
}

void Canvas::onMiddleButtonUp(const Vector2df& position)
{
	ctrl->onMiddleButtonUp(position);
}

void Canvas::onLeftDragging(const Vector2df& position)
{
	ctrl->onLeftDragging(position);
}

void Canvas::onRightDragging(const Vector2df& position)
{
	ctrl->onRightDragging(position);
}

void Canvas::onMiddleDragging(const Vector2df& position)
{
	ctrl->onMiddleDragging(position);
}

void Canvas::onWheel(const float scale)
{
	ctrl->onWheel(scale);
}

Image Canvas::getImage() const
{
	const unsigned int channelNum = 4; // RGBなら3, RGBAなら4
	void* dataBuffer = NULL;
	dataBuffer = (GLubyte*)malloc(width * height * channelNum);

	// 読み取るOpneGLのバッファを指定 GL_FRONT:フロントバッファ　GL_BACK:バックバッファ
	glReadBuffer(GL_BACK);

	// OpenGLで画面に描画されている内容をバッファに格納
	glReadPixels(
		0,                 //読み取る領域の左下隅のx座標
		0,                 //読み取る領域の左下隅のy座標 //0 or getCurrentWidth() - 1
		width,             //読み取る領域の幅
		height,            //読み取る領域の高さ
		GL_RGBA, //it means GL_BGR,           //取得したい色情報の形式
		GL_UNSIGNED_BYTE,  //読み取ったデータを保存する配列の型
		dataBuffer      //ビットマップのピクセルデータ（実際にはバイト配列）へのポインタ
	);

	GLubyte* p = static_cast<GLubyte*>(dataBuffer);

	Image image(width, height);
	int index = 0;
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			const auto r = *p;
			const auto g = *(p + 1);
			const auto b = *(p + 2);
			const auto a = *(p + 3);
			const ColorRGBAuc color(r, g, b, a);
			image.setColor(i, j, color);
			p += 4;
		}
	}
	return image;
}
