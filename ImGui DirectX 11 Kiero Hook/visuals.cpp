#include "visual.h"

namespace visual
{
	void visuals_list()
	{
		if (ImGui::BeginTabItem("Visuals"))
		{

			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::Checkbox("Enemies", &enemy_active);

			ImGui::SameLine();

			ImGui::Dummy(ImVec2(254.9f, 0.0f));

			ImGui::SameLine();

			ImGui::Text("Friendlies");

			ImGui::SameLine();

			ImGui::Checkbox("##Friendlies", &friendly_active);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::Checkbox("Filled", &filled_boxes);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::Checkbox("Unfilled", &unfilled_boxes);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::Checkbox("Corners", &corner_esp);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::Checkbox("Snaplines", &Snaplines);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::Checkbox("Healthbars", &Healthbars);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::Checkbox("Skeletons", &skeleton_esp);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::Checkbox("Player Name", &player_names);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::Checkbox("RGB Enemies", &rgb_enemy);

			ImGui::SameLine();

			ImGui::Dummy(ImVec2(203.5f, 0.0f));

			ImGui::SameLine();

			ImGui::Text("RGB Friendlies");

			ImGui::SameLine();

			ImGui::Checkbox("##RGBFriendlies", &rgb_friendly);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));
			ImGui::SetNextItemWidth(90);

			ImGui::InputFloat("Boldness", &boldness, .25);
			if (boldness > 3)
				boldness = 3;
			else if (boldness < .25)
				boldness = .25;

			ImGui::SameLine();

			ImGui::Dummy(ImVec2(190.f, 0.0f));

			ImGui::SameLine();

			ImGui::Text("Enemies");
			ImGui::SameLine();
			ImGui::ColorEdit3("##EspBoxColorEditor", (float*)&enemy_colors, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::SetNextItemWidth(160);

			ImGui::Combo("##RGBSpeed", &speed_sel, speed_selection, IM_ARRAYSIZE(speed_selection));
			if (speed_sel == 0)
				rgb_speed = 0.3f;
			else if (speed_sel == 1)
				rgb_speed = 0.75f;
			else if (speed_sel == 2)
				rgb_speed = 1.2f;
			else if (speed_sel == 3)
				rgb_speed = 1.5f;

			ImGui::SameLine();

			ImGui::Dummy(ImVec2(168.0f, 0.0f));

			ImGui::SameLine();

			ImGui::Text("Friendlies");
			ImGui::SameLine();
			ImGui::ColorEdit3("##FriendlyEspBoxColorEditor", (float*)&friendly_colors, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

			ImGui::Dummy(ImVec2(0.0f, 3.0f));

			ImGui::EndTabItem();

		}
	}

}