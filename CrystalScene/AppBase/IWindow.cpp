#include "IWindow.h"

using namespace Crystal::UI;

IWindow::~IWindow()
{
	for (auto c : children) {
		delete c;
	}
	children.clear();
};

void IWindow::onShow()
{
	for (auto c : children) {
		c->onShow();
	}
}
