#include "misc.h"

namespace misc
{
	void misc_list()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			if (ImGui::BeginTabBar("#Spoofing", ImGuiTabBarFlags_NoTooltip))
			{
				if (ImGui::BeginTabItem("Spoofing"))
				{
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
								
			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			static auto nameBuffer = ""s;

			ImGui::InputTextWithHint("##NAME", "NAME", &nameBuffer);
			ImGui::SameLine();

			if (ImGui::Button("Set##NAME"))
			{
				strncpy_s(spoofName, sizeof(spoofName), nameBuffer.data(), -1);
				RenamePreGame(spoofName);
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			static auto clan_input = ""s;
			
			ImGui::InputTextWithHint("##CLAN", "CLAN", &clan_input);
			ImGui::SameLine();

			if (ImGui::Button("Set##CLAN"))
			{
				LiveStats_SetClanTagText(0, clan_input.data());
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			static auto info_response_netadr = ""s;

			ImGui::InputTextWithHint("##Netadr", "NETADR", &info_response_netadr);
			ImGui::SameLine();

			if (ImGui::Button("Set##Netadr"))
			{
				spoof_netadr;
				info_response_netadr;
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			if (ImGui::BeginTabBar("#InternExternMsg", ImGuiTabBarFlags_NoTooltip))
			{
				if (ImGui::BeginTabItem("Msg Options"))
				{
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::Checkbox("Chat Msg", &chatmsg);

			ImGui::SameLine();

			ImGui::Checkbox("Internal Msg", &internmsg);

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::Checkbox("Info Request Crash", &crashrtn);

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			if (ImGui::BeginTabBar("#Spoofing1", ImGuiTabBarFlags_NoTooltip))
			{
				if (ImGui::BeginTabItem("Currency"))
				{
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			
			if (div_loop)
			{
				char buf_cmd[255];
				sprintf_s(buf_cmd, "%c %u %u", 120, 3, 120);
				SV_GameSendServerCommand(0, 1, buf_cmd);
			}

			if (ct)
			{
				GiveLootToSelf(0, 1, 1500);
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::Checkbox("Crypto Loop", &ct);

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::Checkbox("Divinium Loop", &div_loop);


			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}