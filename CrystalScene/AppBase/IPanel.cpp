#include "IPanel.h"

#include "imgui.h"
#include <algorithm>

using namespace Crystal::UI;

void IPanel::onShow()
{
	if (!name.empty()) {
		ImGui::Begin(name.c_str());
	}

	for (auto c : children) {
		c->show();
	}
	//std::for_each(children.begin(), children.end(), [](auto c) {c->show(); });

	if (!name.empty()) {
		ImGui::End();
	}
}
