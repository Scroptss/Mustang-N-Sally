#include "tools.h"

namespace tools
{	
	void tools_list()
	{		
		if (ImGui::BeginTabItem("Tools"))
		{
			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			if (ImGui::BeginTabBar("#Options", ImGuiTabBarFlags_NoTooltip))
			{
				if (ImGui::BeginTabItem("Options"))
				{
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
				
			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			static auto join_input = ""s;

			ImGui::InputTextWithHint("##JOIN", "STEAM ID", &join_input);
			ImGui::SameLine();

			if (ImGui::Button("Join##STEAMID"))
			{
				LobbyVM_JoinEvent(0, std::stoull(join_input), JoinType::JOIN_TYPE_PARTY);
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));
	
			if (ImGui::BeginTabBar("#Options1", ImGuiTabBarFlags_NoTooltip))
			{
				if (ImGui::BeginTabItem("Server Cmd"))
				{
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::Dummy(ImVec2(0.0f, 1.4f));
		
			static auto cbuf_input = ""s;		

			ImGui::InputTextWithHint("##CBUF", "CBUF", &cbuf_input);
			ImGui::SameLine();

			if (ImGui::Button("Send##CBUF"))
			{
				Cbuf_AddText(0, cbuf_input.data());
			}

			static auto single_input = ""s;

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::InputTextWithHint("##SINGLE", "SINGLE", &single_input);
			ImGui::SameLine();

			if (ImGui::Button("Send##SINGLE"))
			{
				Cmd_ExecuteSingleCommand(0, 0, single_input.data(), false);
			}

			static auto reliable_input = ""s;

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::InputTextWithHint("##RELIABLE", "RELIABLE", &reliable_input);

			ImGui::SameLine();

			if (ImGui::Button("Send##RELIABLE"))
			{
				CL_AddReliableCommand(0, reliable_input.data());
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));
	
			static auto callvote_input = ""s;
			
			ImGui::InputTextWithHint("##Callvote", "CALLVOTE", &callvote_input);

			ImGui::SameLine();

			if (ImGui::Button("Send"))
			{
				char cmd[255];
				sprintf_s(cmd, "callvote map \"%s\"", callvote_input.data());
				CL_AddReliableCommand(0, cmd);
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			static auto print_bold = ""s;
			
			ImGui::InputTextWithHint("##iPrintBold", "PRINT BOLD", &print_bold);

			ImGui::SameLine();

			if (ImGui::Button("Print"))
			{
				char Buffer[1030];
				sprintf_s(Buffer, "< \"%s\"\n", print_bold.data());
				SV_GameSendServerCommand(0, 1, (char*)Buffer);
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));
				
			{
				void CBUF(int al, char* a2);
			}

			ImGui::EndTabItem();
		}
	}

}