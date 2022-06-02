#include "ComboBox.h"
#include "imgui.h"

using namespace Crystal::UI;

void ComboBox::add(const std::string& label, const std::function<void(void)> func)
{
    labelFuncMap[label] = func;
}

void ComboBox::onShow()
{
	auto str = name.c_str();
    auto current_item = selectedLabel.c_str();

    if (ImGui::BeginCombo(str, current_item)) { // The second parameter is the label previewed before opening the combo.
        for (const auto& m : labelFuncMap) {
            auto sstr = m.first.c_str();
            bool is_selected = (current_item == sstr); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(sstr, is_selected)) {
                selectedLabel = m.first;
            }
            if (is_selected) {
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
        }
        ImGui::EndCombo();
    }

    //ImGui::SameLine();

    //ImGui::Text(str);
}

std::string ComboBox::getSelected() const
{
    return selectedLabel;
}