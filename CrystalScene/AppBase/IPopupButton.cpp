#include "IPopupButton.h"
#include "imgui.h"

using namespace Crystal::UI;

void IPopupButton::onShow()
{
	const auto nameStr = name.c_str();
	if (ImGui::Button(nameStr)) {
		ImGui::OpenPopup(nameStr);
	}
	if (ImGui::BeginPopup(nameStr)) {
		onShow();
		if (ImGui::Button("OK")) {
			onOk();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::Button("Cancel")) {
			onCancel();
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}