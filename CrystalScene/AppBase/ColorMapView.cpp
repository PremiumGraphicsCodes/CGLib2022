#include "ColorMapView.h"

#include "../../Crystal/Graphics/ColorHSV.h"

#include "imgui.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

ColorMapView::ColorMapView(const std::string& name /*, const ColorMap& value */) :
	IView(name),
	value(value),
	resolution("Resolution", value.getTable().getResolution()),
	minValue("MinValue", value.getMin()),
	maxValue("MaxValue", value.getMax())
{
    const ColorTable table = ColorTable::createDefaultTable(270);
    this->value = ColorMap(0.0, 1.0, table);

	/*
	Graphics::Image img(value.getResolution(), 32);
	for (int i = 0; i < value.getResolution(); ++i) {
		for (int j = 0; j < 32; ++j) {
			const auto color = value.getColorFromIndex(i);
			img.setColor(i, j, Crystal::Graphics::toColorRGBAuc(color));
		}
	}
	*/

	//ImDrawList* draw_list = ImGui::GetWindowDrawList();
	//draw_list->AddRectFilledMultiColor()
}

void ColorMapView::onShow()
{
    ImGui::BeginGroup();
    ImGui::PushID(name.c_str());
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    // setup
    ImVec2 picker_pos = ImGui::GetCursorScreenPos();

    std::vector<ImColor> colors;
    //colors[0] = ImColor(255,0, 0);
    //colors[1] = ImColor(255,0, 0);
    //colors[2] = 1.0;
    for (int i = 0; i < 100; ++i) {
        const auto c = value.getColor(i / 100.0f);
        ImColor ic(c.r, c.g, c.b);
        colors.push_back(ic);
    }

    for (int i = 0; i < colors.size()-1; ++i) {
        const auto x = picker_pos.x + i * 2;
        draw_list->AddRectFilledMultiColor
        (
            ImVec2(x, picker_pos.y),
            ImVec2(x + 2, picker_pos.y + 10),
            colors[i],
            colors[i],
            colors[i+1],
            colors[i+1]
        );

        //ImGui::ItemAddButton()
        //draw_list->AddLine(ImVec2(x, picker_pos.y),
        //    ImVec2(x + 10, picker_pos.y), colors[0]);
        //ItemAdd
    }

    // keep layout.
    ImGui::InvisibleButton("hue_selector", ImVec2(100, 10));

    ImGui::PopID();
    ImGui::EndGroup();

    //ColorPicker()
}
